#include "httplib.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// We wrap your core calculations inside a function that returns a string result
string solve_congruences(int a1, int a2, int a3, int n1, int n2, int n3) {
    stringstream ss;

    // Check whether the modulos are valid
    if (n1 == 0 || n2 == 0 || n3 == 0) {
        return "Error: Invalid input of modulo. Modulos cannot be 0.";
    }

    int i, j, k, hcf1 = 1, hcf2 = 1, hcf3 = 1, N, Y;

    // Check for the highest common factor (hcf)
    for (i = 1; i <= n1 && i <= n2; i++) {
        if (n1 % i == 0 && n2 % i == 0) hcf1 = i;
    }

    for (j = 1; j <= n1 && j <= n3; j++) {
        if (n1 % j == 0 && n3 % j == 0) hcf2 = j;
    }

    for (k = 1; k <= n2 && k <= n3; k++) {
        if (n2 % k == 0 && n3 % k == 0) hcf3 = k;
    }

    if (hcf1 != 1 || hcf2 != 1 || hcf3 != 1) {
        ss << "Error: " << n1 << ", " << n2 << ", and " << n3 << " are not pairwise co-prime.";
        return ss.str();
    }

    // Calculations
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

    // Build the output string to send back to the webpage
    ss << "System of congruences solved successfully!\n\n"
       << "x % " << n1 << " = " << a1 << "\n"
       << "x % " << n2 << " = " << a2 << "\n"
       << "x % " << n3 << " = " << a3 << "\n\n"
       << "Solution: " << Y << " modulo " << N;

    return ss.str();
}

int main(void) {
    httplib::Server svr;

    // Expose a GET endpoint at http://localhost:8080/api/solve
    svr.Get("/api/solve", [](const httplib::Request& req, httplib::Response& res) {
        // Essential: Allows your webpage to access this backend without security blockers
        res.set_header("Access-Control-Allow-Origin", "*"); 

        // Check if all 6 parameters are provided in the URL link
        if (req.has_param("a1") && req.has_param("a2") && req.has_param("a3") &&
            req.has_param("n1") && req.has_param("n2") && req.has_param("n3")) {
            
            // Extract and convert text from web request into integers
            int a1 = stoi(req.get_param_value("a1"));
            int a2 = stoi(req.get_param_value("a2"));
            int a3 = stoi(req.get_param_value("a3"));
            int n1 = stoi(req.get_param_value("n1"));
            int n2 = stoi(req.get_param_value("n2"));
            int n3 = stoi(req.get_param_value("n3"));

            // Run your calculation logic
            string result = solve_congruences(a1, a2, a3, n1, n2, n3);
            
            res.set_content(result, "text/plain");
        } else {
            res.status = 400;
            res.set_content("Error: Missing inputs. Please provide a1, a2, a3, n1, n2, n3.", "text/plain");
        }
    });

    cout << "CRT Solver Server running at http://localhost:8080" << endl;
    svr.listen("0.0.0.0", 8080);
    return 0;
}
