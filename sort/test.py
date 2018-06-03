import merge_sort
import shell_sort
import heap_sort
import bubble_sort
import insertion_sort
import selection_sort
import quick_sort


import pickle
file  = open("data.pkl", "rb")
data = pickle.load(file)
file.close()

#merge_sort.merge_sort(data)
#insertion_sort.insertion_sort(data)
#heap_sort.heap_sort(data)
#bubble_sort.bubble_sort(data)
#shell_sort.shell_sort(data)
#selection_sort.selection_sort(data)
quick_sort.quick_sort(data, 0, len(data))
print bubble_sort.isSorted(data)
