get_numbers = (nbrs_as_str) => {
    var nbrs_arr = [];
    var split = nbrs_as_str.split(' ');
    var tmp = 0;

    for (i = 0; i < split.length; i++) {
        tmp = Number(split[i]);
        if (isNaN(tmp))
            return null;
        nbrs_arr.push(tmp);
    }
    return nbrs_arr;
};

partition = (nbrs_arr, first_idx, last_idx) => {
    var next_pivot_idx = first_idx;
    var pivot = nbrs_arr[last_idx];

    for (i = first_idx; i < last_idx; i++)
        if (nbrs_arr[i] <= pivot) {
            [nbrs_arr[i], nbrs_arr[next_pivot_idx]] =
            [nbrs_arr[next_pivot_idx], nbrs_arr[i]];
            next_pivot_idx++;
        }
    [nbrs_arr[last_idx], nbrs_arr[next_pivot_idx]] =
    [nbrs_arr[next_pivot_idx], nbrs_arr[last_idx]];
    return next_pivot_idx;
};

quick_sort = (nbrs_arr, first_idx, last_idx) => {
    if (first_idx >= last_idx)
        return;
    pivot_idx = partition(nbrs_arr, first_idx, last_idx);
    quick_sort(nbrs_arr, first_idx, pivot_idx - 1);
    quick_sort(nbrs_arr, pivot_idx + 1, last_idx);
};

is_sorted = (nbrs_arr) => {
    for (i = 0; i < nbrs_arr.length; i++)
        for (j = i + 1; j < nbrs_arr.length; j++)
            if (nbrs_arr[i] > nbrs_arr[j])
                return false;
    return true;
};

launch_sort = (nbrs_as_str) => {
    var nbrs_arr = [];

    nbrs_as_str = nbrs_as_str.replace(/\s+/g, " ").trim();
    if (!nbrs_as_str.length)
        return null;
    if (!(nbrs_arr = get_numbers(nbrs_as_str)))
        return null;
    if (nbrs_arr.length == 1)
        return String(nbrs_arr[0]);
    quick_sort(nbrs_arr, 0, nbrs_arr.length - 1);
    return nbrs_arr;
};