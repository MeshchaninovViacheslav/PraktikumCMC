int main() {
    int count;
    std::cin >> count;

    Holder* buf = new Holder[count]();
    for (int i = 0; i < count / 2; i++) {
        buf[i].swap(buf[count - i - 1]);
    }
    delete[] buf;
}