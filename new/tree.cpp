#include <iostream>
#include <algorithm>

using namespace std;

    int main() {
    int arr[7];
    int n = 7;

    for (int i = 0; i < 7; i++) {
        cout << "请输入第 " << i + 1 << " 个数字: ";
        cin >> arr[i];
    }

    for (int i = 0; i < n; i ++ )
        for (int j = i + 1; j < n; j ++ )
            if (arr[i] < arr[j])
                swap(arr[i], arr[j]);

    for (int i = 0; i < n; i ++ ) cout << arr[i] << ' ';
    cout << endl;

    return 0;
}

