const web_buffer = document.getElementById("buffer");
const gen_btn = document.getElementById("gen_btn");
const js_btn = document.getElementById("js_btn");
const wasm_btn = document.getElementById("wasm_btn");
const js_sort = document.getElementById("js_sort");
const js_run_time = document.getElementById("js_run_time");
const wasm_sort = document.getElementById("wasm_sort");
const wasm_run_time = document.getElementById("wasm_run_time");

const launch_sort_wasm = Module.cwrap('launch_sort', 'string', ['string']);

tell_len = () => {
    var input = prompt("Please enter the numbers of numbers you want generate:");
    var len = 0;

    if (!input)
        return null;
    len = Number(input);
    while (isNaN(len) || len <= 0) {
        if (!(input = prompt("Please enter positive non null integer.")))
            return null;
        len = Number(input);
    }
    return len;
};

tell_min = () => {
    var input = prompt("Please enter the minimal value you want of number:");
    var min = 0;

    if (!input)
        return null;
    min = Number(input);
    while (isNaN(min)) {
        if (!(input = prompt("Please enter integer.")))
            return null;
        min = Number(input);
    }
    return min;
};

tell_max = (min) => {
    var input = prompt("Please enter the maximal value you want of numbers:");
    var max = 0;

    if (!input)
        return null;
    max = Number(input);
    while (isNaN(max) || max <= min) {
        if (!(input = prompt(`Please enter integer greater than minimal value (${min}).`)))
            return null;
        max = Number(input);
    }
    return max;
};

generate_numbers = (len, min, max) => {
    var arr = new Array(len);

    for (i = 0; i < len; i++)
        arr[i] = Math.floor(Math.random() * (max - min + 1) + min);
    return format_numbers(arr, len);
};

gen_btn.addEventListener("click", (event) => {
    var len = 0;
    var min = 0;
    var max = 0;

    if ((len = tell_len()) == null ||
        (min = tell_min()) == null ||
        (max = tell_max(min)) == null)
        return;
    web_buffer.value = generate_numbers(len, min, max);
});

js_btn.addEventListener("click", (event) => {
    var timer = Date.now();
    var sort = launch_sort(web_buffer.value);
    var run_time = Date.now() - timer;

    if (sort) {
        js_run_time.innerHTML = `Sorted numbers in ${run_time} milliseconds.`;
        js_sort.innerHTML = sort;
    } else
        js_sort.innerHTML = "Error: invalid input.";
});

wasm_btn.addEventListener("click", (event) => {
    var timer = Date.now();
    var sort = launch_sort_wasm(web_buffer.value);
    var run_time = Date.now() - timer;

    if (sort) {
        wasm_run_time.innerHTML = `Sorted numbers in ${run_time} milliseconds.`;
        wasm_sort.innerHTML = sort;
    } else
        wasm_sort.innerHTML = "Error: invalid input or out of memory.";
});