// 1, 3, 4, 8, 1, 6
def bubble_sort(arr, Closure compare = {a, b -> a > b})
{
    assert arr != null
    for(int i = arr.size()-1; i > 0; --i)  //µÝ¼õ - the last number that fixed
    {
        for(int j = 0; j < i; ++j)         //µÝÔö - loop through the subset to bubble the larget one.
        {
            if(compare(arr[j], arr[j+1]))
            {
                def tmp = arr[j]
                arr[j] = arr[j+1]
                arr[j+1] = tmp
            }
        }
    }
    println arr
    
}


bubble_sort([1])
bubble_sort([2,1])
bubble_sort([1,2])
bubble_sort([3,1,2])
bubble_sort([1,2, 3])
bubble_sort([1,2, 3, 0, 1, 34, 23, 1, 3, 4, 9, 7]) {a, b -> a < b}
