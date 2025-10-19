#include "app/Application.h"

int main() {
    AplikasiToko app("users.csv", "items.csv", "transactions.csv");
    app.jalankan();
    return 0;
}