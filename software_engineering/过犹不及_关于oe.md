### 过度包装
```
/*
 *  over engineering.
 * */
  static_cast<TFSWrapperOpNodePerGraphData *>(per_graph_data_[graph_idx])->source_idx_ =
      static_cast<TranslateSenIdxNode *>(per_graph_data_[graph_idx]->op_node_sketch_->input_data_nodes_[0].data_sketch_node->global_data_node_->data_nodes_per_thread_[tid]);

  static_cast<TFSWrapperOpNodePerGraphData *>(per_graph_data_[graph_idx])->target_idx_ =
      static_cast<TranslateSenIdxNode *>(per_graph_data_[graph_idx]->op_node_sketch_->output_data_nodes_[0].data_sketch_node->global_data_node_->data_nodes_per_thread_[tid]);
```
