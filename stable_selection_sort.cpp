#include <iostream>

void print_array(int *tab, int n, std::string comment) {
    if (!tab || n <= 1) return;
    //print array in format comment (a,b,c,d)
    std::cout << comment + "(";
    for (int i = 0; i < n-1; i++){
        std::cout << tab[i] << ",";
    }
    std::cout << tab[n-1] << ")" << std::endl;
}

bool check_if_sorted(int *tab, int n) {
    //check if the array tab is sorted by looking at all subarrays
    if (n == 1 || n == 0) {
        return true;
    }
    return (tab[n-1] >= tab[n-2]) && check_if_sorted(tab,n-1);
}

bool check_keys(int *tab, int *keys, int n) {
    //check if the keys are good (for same number they are ascending)
    bool key_good = true;
    for (int i = 1; i < n; i++) {
        if (tab[i] == tab[i-1] && keys[i] < keys[i-1]) {
            key_good = false;
        }
    }
    return key_good;
}

void swap_values(int *tab, int i, int j) {
    if (!tab) return;
    int temp = tab[j];
    tab[j] = tab[i];
    tab[i] = temp;
};

bool stabilization_pass(int *tab, int *keys, int n) {
    bool key_good;                                          //flag to see if the keys are ok
    for (int i = 1; i < n; i++) {
        if (tab[i] == tab[i-1] && keys[i-1] > keys[i]) {
            swap_values(keys,i,i-1);                        //if not fine we swap keys
            swap_values(tab,i,i-1);                         //we do it in the array too
            key_good = check_keys(tab,keys,n);              //we check if that stabilized everything
        }
    }
    return key_good;                                        //was that stabilization pass a success ? 
}

void stabilization(int *tab, int *keys, int n) {
    if (!tab || n <= 1) return;
    bool key_good = false;
    //we do stabilization pass as long as the keys are not in a good order
    while (!key_good) {
        key_good = stabilization_pass(tab,keys,n);
    }
}

void selection_sort_pass(int *tab, int *keys, int n, int iter) {
    int index_min = iter-1;             //minimum value
    int min_value = tab[iter-1];        //and it's position, both to be updated
    for (int i = iter; i < n; i++) {
        if (tab[i] < min_value) {
            index_min = i;              //new minimum
            min_value = tab[i];         //and it's position
        }
    }
    swap_values(tab,index_min,iter-1);  //selection sort
    swap_values(keys,index_min,iter-1); //effect on the position keys (for stabilization)
}

void selection_sort(int *tab, int n, bool print_keys) {
    if (!tab || n <= 1) return;
    //we create an keys array
    int keys[n];
    for (int i = 0; i < n; i++) {
        keys[i] = i;
    }

    //we do the selection sort
    for (int i = 1; i < n; i++) {
        selection_sort_pass(tab,keys,n,i);
    }

    //key of same numbers should be ascending if stable
    if (print_keys) {//print only if needed
        print_array(keys,n,"\nKeys positions after selection sort :\t");
        stabilization(tab,keys,n);
        print_array(keys,n,"\nKeys positions after stabilization :\t");
    } else {
        stabilization(tab,keys,n);
    }

    //verification if the selection sort is stable in the end
    int key_good = check_keys(tab,keys,n);
    if (key_good == 0) {
        std::cout << "\nThe sort is not stable.. " << std::endl;
    }
}

int main() {
    int tab[] = {3,5,2,8,1,7,5,4,2,9,3,6,7,2,1,5};
    int n = sizeof(tab)/sizeof(tab[0]);
    print_array(tab,n,"\nStart array :\t");

    selection_sort(tab,n,true);
    print_array(tab,n,"\nSorted array :\t");
    return 0;
}
