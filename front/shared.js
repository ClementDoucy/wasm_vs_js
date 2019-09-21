format_numbers = (arr, len) => {
    var str = "";

    arr.forEach((value, i) => {
        str += value;
        if (i != len - 1)
            str += ' ';
    });
    return str;
};