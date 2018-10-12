import bin_tree_lib

tree = bin_tree_lib.build_bin_tree()
bin_tree_lib.post_traverse_non_recursive(tree)
print
bin_tree_lib.pre_traverse_non_recursive(tree)
print
bin_tree_lib.middle_traverse_non_recursive(tree)
