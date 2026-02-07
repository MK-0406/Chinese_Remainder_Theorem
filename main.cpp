#include <iostream>
#include <string>

using namespace std;

int main(void) {

    // Declare integers.
    int a1, a2, a3, n1, n2, n3, i, j, k, hcf1, hcf2, hcf3, N, Y;

    // Input list of three remainders and list of three modulos.
    cout << "Please enter the list of remainders:\n";
    cin >> a1 >> a2 >> a3;
    cout << endl;
    cout << "Please enter the list of modulos:\n";
    cin >> n1 >> n2 >> n3;
    cout << endl;

    // Check whether the modulos is valid.
    if (n1 == 0 || n2 == 0 || n3 == 0)
        cout << "Invalid input of modulo." << endl << endl;

    // Check for the highest common factor (hcf)
    else {
        for (i = 1; i < n1 || i < n2; i++) {
            if (n1 % i == 0 && n2 % i == 0)
                hcf1 = i;
        }

        for (j = 1; j < n1 || j < n3; j++) {
            if (n1 % j == 0 && n3 % j == 0)
                hcf2 = j;
        }

        for (k = 1; k < n2 || k < n3; k++) {
            if (n2 % k == 0 && n3 % k == 0)
                hcf3 = k;
        }

        if (hcf1 != 1 || hcf2 != 1 || hcf3 != 1)
            cout << n1 << " " << n2 << " " << n3 << " are not pairwise co-prime."
            << endl << endl;

        // Calculations
        else {
            cout << "The system of congruences to be solved is:" << endl;

            cout << "x % " << n1 << " = " << a1 << endl;
            cout << "x % " << n2 << " = " << a2 << endl;
            cout << "x % " << n3 << " = " << a3 << endl;

            int m1, m2, m3, mi1, mi2, mi3;

            N = n1 * n2 * n3;

            m1 = N / n1;
            m2 = N / n2;
            m3 = N / n3;

            mi1 = m1 % n1;
            mi2 = m2 % n2;
            mi3 = m3 % n3;

            Y = (a1 * m1 * mi1) + (a2 * m2 * mi2) + (a3 * m3 * mi3);
            Y = Y % N;

            // Results
            cout << "\nThe system of congruences has the solution " << Y
                << " modulo " << N << endl << endl;
        }
    }
    // End
    system("PAUSE");
    return 0;
}