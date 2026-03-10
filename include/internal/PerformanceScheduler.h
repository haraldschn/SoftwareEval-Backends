#ifndef SWEVAL_BACKENDS_PERFORMANCE_SCHEDULER_H
#define SWEVAL_BACKENDS_PERFORMANCE_SCHEDULER_H

#include <iostream>
#include <cstdint>

#include <sstream>
#include <string>

#include <vector>
#include <queue>
#include <unordered_set>

class ResourceGraph {
   private:
    bool debug;

    const uint32_t* RES_Capacity;

    void print_set(std::unordered_set<uint64_t>& input) {
        std::cout << "{";

        if (input.empty()) {
            std::cout << "}\t";
            return;
        }

        for (auto it = input.begin(); it != input.end();) {
            std::cout << *it;
            if (++it != input.end()) {
                std::cout << ", ";
            }
        }

        std::cout << "}\t";
    };

    int type_length = 1;
    struct Node {
        // General node values
        uint64_t operands_ready = UINT64_MAX;
        uint64_t id = 0;
        uint64_t inorder_prev = 0;

        // Enum in CPU specific PerformanceModel used for type identifier
        int type = 0;

        // Latency by default set to a large value (has to be set in any of the later usages)
        uint64_t latency = 1;
        uint64_t t_LR = 0;
        uint64_t t_exit = 0;

        // Stage handling
        uint64_t next_stage = 0;  // next stage (0 if none)

        // Parent Child relation
        uint64_t parent = 0;      // parent stage (0 if none)
        int children_unfinished = -1;

        // IDs to predecessor and successor nodes
        std::vector<uint64_t> preds;
        std::vector<uint64_t> succs;
    };

    // this is the structure which implements the
    // operator overloading for Node comparision using std::greater
    struct CompareNodes {
        bool operator()(const Node& a, const Node& b) {
            // operands_ready inorder prev.
            if (a.inorder_prev != b.inorder_prev) {
                return a.inorder_prev > b.inorder_prev;  // lower
            }
            // operands_ready in ascending order.
            if (a.operands_ready != b.operands_ready) {
                return a.operands_ready > b.operands_ready;  // lower
            }
            // id in ascending order.
            return a.id > b.id;  // lower
        }
    };

    std::vector<Node> nodes;
    std::unordered_set<uint64_t> ready_nodes;

    std::vector<std::unordered_set<uint64_t>> U_act;
    std::vector<std::unordered_set<uint64_t>> T_act;
    std::vector<std::unordered_set<uint64_t>> S_act;

    uint64_t t_curr = 1;

   public:
    ResourceGraph(int type_len, bool debug_in = false) {
        type_length = type_len;
        debug = debug_in;

        Node root_node;
        root_node.id = 0;
        root_node.type = 0;
        root_node.latency = 0;
        nodes.push_back(root_node);

        for (int i = 0; i < type_len; i++) {
            std::unordered_set<uint64_t> U_0;
            std::unordered_set<uint64_t> T_0;
            std::unordered_set<uint64_t> S_0;

            U_act.push_back(U_0);
            T_act.push_back(T_0);
            S_act.push_back(S_0);
        }

        std::cout << "Resource Graph INIT" << "\n";
    };
    ~ResourceGraph() = default;

    void init_capacity(const uint32_t RES_Cap[]) {
        this->RES_Capacity = RES_Cap;
    }

    uint64_t add_node(int type, uint64_t latency = 1, uint64_t parent_idx = 0) {
        Node node_new;

        node_new.type = type;
        node_new.latency = latency;

        nodes.push_back(node_new);
        uint64_t id = nodes.size() - 1;
        nodes[id].id = id;

        if (parent_idx != 0) {
            nodes[id].parent = parent_idx;
            nodes[parent_idx].children_unfinished += 1;

            for (uint64_t p : nodes[parent_idx].preds) {
                add_edge(p, id);
            }

            if (nodes[parent_idx].preds.empty()) {
                ready_nodes.insert(id);
            }
        }

        return id;
    }

    uint64_t add_parent_node(int type, uint64_t parent_idx = 0) {
        uint64_t id = add_node(type, 1, parent_idx);
        nodes[id].children_unfinished = 0;

        return id;
    }

    void add_edge(const uint64_t& from, const uint64_t& to) {
        if (from != 0) {
            nodes[to].preds.push_back(from);
            nodes[from].succs.push_back(to);
        } else if (nodes[to].succs.size() == 0) {
            ready_nodes.insert(to);
        }
    }

    void add_stage_connection(const uint64_t& prev_stage, const uint64_t& curr_stage) {
        add_edge(prev_stage, curr_stage);
        nodes[prev_stage].next_stage = curr_stage;
    }

    void set_inorder(const uint64_t& prev, const uint64_t& curr) {
        nodes[curr].inorder_prev = prev;
    }

    void find_candidate_operations(uint64_t t) {
        std::vector<uint64_t> delete_stack;

        for (uint64_t id : ready_nodes) {
            bool all_finished = true;
            uint64_t max_pred_finished = 0;
            for (uint64_t p : nodes[id].preds) {
                uint64_t t_pred_finish = nodes[p].t_exit;
                // Predecessor order influences runtime
                if (nodes[p].t_LR == 0 || t_pred_finish > t || nodes[p].children_unfinished > 0) {
                    all_finished = false;
                    break;
                }
                max_pred_finished = std::max(max_pred_finished, t_pred_finish);
            }

            if (all_finished) {
                int k = nodes[id].type;
                U_act[k].insert(nodes[id].id);
                delete_stack.push_back(id);
                nodes[id].operands_ready = max_pred_finished;
            }
        }

        for (uint64_t id : delete_stack) {
            ready_nodes.erase(id);
        }
    }

    void find_running_operations(uint64_t t, int k) {
        std::vector<uint64_t> delete_stack;

        for (uint64_t id : S_act[k]) {
            T_act[k].insert(id);
        }

        for (uint64_t id : T_act[k]) {
            uint64_t next_stage = nodes[id].next_stage;

            if (next_stage == 0) {
                if (nodes[id].t_exit <= t) {
                    delete_stack.push_back(id);
                }
            } else {
                if (nodes[id].t_exit <= t && nodes[next_stage].t_LR >= t) {
                    delete_stack.push_back(id);
                } else if(nodes[id].t_exit <= t) {
                    nodes[id].t_exit++;
                }
            }
        }

        for (uint64_t id : delete_stack) {
            int k = nodes[id].type;
            T_act[k].erase(id);
        }
    }

    void schedule(uint64_t last_node, bool finish_schedule = false) {
        // std::cout << "ready_node.size() = " << ready_nodes.size() << "\n";

        nodes[0].t_LR = 1;

        while (nodes[last_node].t_LR == 0 || (finish_schedule && ready_nodes.size() > 0)) {
            find_candidate_operations(t_curr);

            for (int k = 1; k < type_length; k++) {
                find_running_operations(t_curr, k);

                S_act[k].clear();

                // pq could be represented by using a priority_queue for U_act ?
                std::priority_queue<Node, std::vector<Node>, CompareNodes> pq;
                for (auto& u : U_act[k]) {
                    pq.push(nodes[u]);
                }

                while (!pq.empty() && (S_act[k].size() + T_act[k].size() < RES_Capacity[k])) {
                    int id_max = pq.top().id;
                    pq.pop();

                    if(nodes[id_max].inorder_prev != 0 && nodes[nodes[id_max].inorder_prev].operands_ready == UINT64_MAX) {
                        break;
                    }

                    uint64_t parent_id = nodes[id_max].parent;
                    if (parent_id != 0) {
                        if (nodes[parent_id].t_LR == 0) {
                            continue;
                        } else {
                            nodes[parent_id].children_unfinished -= 1;
                        }
                        
                    }

                    S_act[k].insert(id_max);
                    nodes[id_max].t_LR = t_curr;
                    nodes[id_max].t_exit = t_curr + nodes[id_max].latency;

                    // Add succesors to ready nodes
                    for (uint64_t s : nodes[id_max].succs) {
                        ready_nodes.insert(s);
                    }
                }

                if (debug && (!U_act[k].empty() || !T_act[k].empty() || !S_act[k].empty())) {
                    std::cout << "t:" << t_curr << "\n";
                    std::cout << "k:" << k << "\n";
                    std::cout << "\t\tU_act:";
                    print_set(U_act[k]);
                    std::cout << "T_act:";
                    print_set(T_act[k]);
                    std::cout << "S_act:";
                    print_set(S_act[k]);
                    std::cout << "\n";
                }

                for (auto it = S_act[k].begin(); it != S_act[k].end(); ++it) {
                    U_act[k].erase(*it);
                }
            }

            t_curr += 1;
        }

        // Multi-issue adaption:
        // allows stage times to be equal althoug next instruction is added after calling schedule function
        t_curr -= 1;
    }

    /// helper functions for std output

    size_t get_nodes_len() {
        return nodes.size();
    }

    std::string get_priority_str(uint64_t id) {
        std::stringstream ret_strs;

        ret_strs << "(";
        ret_strs << nodes[id].operands_ready;
        ret_strs << ",";
        ret_strs << nodes[id].id;
        ret_strs << ")";

        return ret_strs.str();
    }

    uint64_t get_node_t_start(uint64_t curr_node_id) {
        return nodes[curr_node_id].t_LR - 1;
    }

    uint64_t get_node_t_end(uint64_t curr_node_id) {
        return nodes[curr_node_id].t_exit - 1;
    }

    uint64_t get_node_t_end(uint64_t curr_node_id, uint64_t print_node_id, int type) {
        if (type == nodes[curr_node_id].type) {
            return nodes[print_node_id].t_LR - 1;
        }

        return 0;
    }
};

#endif