#include<iostream>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<iomanip>
using namespace std;

class CStr {
private:
    char length[21];
    static const char* Gen(int len =-1)
    {
        static char s[21];
        static const char cs[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        int n;
        if (len < 0) n = rand() % 20 + 1;
        else if (len > 20)n = 20;
        else n = len;
        for (int i = 0; i < n; ++i) s[i] = cs[rand() % 62];
        s[n] = '\0';
        return s;
    }
public:
    CStr() {
        strcpy_s(length, Gen());
    }
    CStr(const char* cst) {
        int i = 0;
        if (cst) {
            while (i < 20 && cst[i] != '\0') {
                length[i] = cst[i];
                ++i;
            }
        }
        length[i] = '\0';
    }
    CStr(int len) {
        if (len < 0)len = 0;
        if (len > 20)len = 20;
        strcpy_s(length, Gen(len));

    }
    CStr(const CStr& CStr1) {
        strcpy_s(length, CStr1.length);
    }
    ~CStr() {}

    CStr& operator=(const CStr& CStr1)
    {
        if (this != &CStr1)
            strcpy_s(length, CStr1.length);
        return *this;
    }
    CStr& operator=(const char* cst)
    {
        int i = 0;
        if (cst) {
            while (i < 20 && cst[i] != '\0') {
                length[i] = cst[i];
                ++i;
            }
        }
        length[i] = '\0';
        return *this;
    }
    bool operator>(const CStr& CStr1)const {
        return strcmp(length, CStr1.length) > 0;
    }
    bool operator<(const CStr& CStr1) const {
        return strcmp(length, CStr1.length) < 0;
    }
    CStr& operator+=(const CStr& CStr1)
    {
        int cur = (int)strlen(length);
        int add = (int)strlen(CStr1.length);
        int space = 20 - cur;
        if (add > space) add = space;
        if (add > 0) std::memcpy(length + cur, CStr1.length, add);
        length[cur + add] = '\0';
        return *this;
    }
    CStr operator+(const CStr& CStr1) const
    {
        CStr r(*this);
        r += CStr1;
        return r;
    }
    char& operator[](int i) { 
        return length[i]; 
    }
    int String_Len()const {
        return(int)strlen(length);
    }

    friend ostream& operator << (ostream& os, const CStr& cst) {
        os << cst.length;
        return os;
    }
    friend istream& operator >> (istream& is, CStr& cst) {
        char s[21];
        is >> setw(21) >> s;
        cst = s;
        return is;
    }
};
    class CStrArray {
    private:
            CStr**arr;
            int size;
            int rongliang;
    public:
        CStrArray() {
            size = 0;
            rongliang = 2;
            arr =new CStr*[rongliang];
            for (int i = 0; i < rongliang; ++i) {
                arr[i] = nullptr;
            }
        }
        CStrArray& operator += (CStr& cstr) {
            if (size>=rongliang) {
                rongliang = rongliang * 2;
                CStr**new_arr = new CStr * [rongliang];
                for (int i = 0; i < size;++i) {
                    new_arr[i] = arr[i];
                }
                delete[]arr;
                arr = new_arr;
            }
            arr[size] = &cstr;
            size++;
            return *this;
        }

        ~CStrArray() {
            delete[]arr;
        }

        CStr* operator[](int i)
        {
            if (i >= 0 && i < size) {
                return arr[i];
            }
            return nullptr;
        }
        void neirongpaixu() {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size - i - 1;++j) {
                    if (*arr[j] > *arr[j + 1]) {
                        CStr* temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                    
                }
            }
        }
        void changdupaixu() {
            for (int j = 0; j < size; ++j) {
                for (int i = 0; i < size - j - 1; ++i) {
                    if (arr[i]->String_Len() > arr[i + 1]->String_Len()) {
                        CStr* temp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = temp;
                    }
                }
            }
        }
        bool massyouxu()const {
            if (size <= 1)return 1;
            for (int i = 0; i < size-1; ++i) {
                if (*arr[i] > *arr[i + 1]) {
                    return 0;
                }
            }
            return 1;
        }
        friend ostream& operator<<(ostream&os,CStrArray&array ) {
            for (int i = 0; i < array.size; ++i) {
                if (array.arr[i] != nullptr) {
                    os << "[" << i << "]: " << *array.arr[i] << "\n";
                }
            }
            return os;
        }

    };

int main() {
    srand((unsigned)time(nullptr));
    CStr c0(10); cout << c0 << endl;
    CStr c10(11); cout << c10 << endl;
    cout << (c10 < c0) << endl;
    cout << c0 + c10 << endl;;
    CStrArray arrayq;
    arrayq += c0;
    arrayq += c10;
    arrayq.neirongpaixu();
    cout << arrayq << endl;

    arrayq.massyouxu();
    cout << arrayq << endl;
    cout << *arrayq[1] << endl;;
    CStr c1;
    cout << "c1 " << c1 << endl;
    CStr c2("qwdri123929ASAD");
    cout << "c2 " << c2 << endl;
    CStr c3(10);
    cout << "c3 " << c3 << endl;
    CStr c4(c2);
    cout << "c4 " << c4 << endl;

    CStr c5;
    c5 = c4;
    cout << "c5 " << c5 << endl;
    CStr c6;
    c6 = "world";
    cout << "c6 " << c6 << endl;

    CStr c7 = c2;
    c7 += c6;
    cout << "c7 " << c7 << endl;
    CStr c8 = c2 + c5;
    cout << "c8 " << c8 << endl;

    cout << "c2[0]=" << c2[0] << ",c2[1]=" << c2[1] << endl;

    CStr a("apple"), b("banana");
    cout << "a<b=" << (a < b) << endl;
    cout << "a>b=" << (a > b) << endl;

    cout << "c2.length()=" << c2.String_Len() << endl;
    cout << "c6.length()=" << c6.String_Len() << endl;

    CStr input;
    cin >> input;
    cout << "input:" << input << endl;
    CStr putout;
    cin >> putout;
    cout << "putout:" << putout << endl;
    cout << "class CStrArray: " << endl;
    //------------------------------------------------------------
    CStrArray array;
    
    array += c1;
    array += c2;
    array += c7;
    array += c4;
    array += c8;
    array += c6;
    cout << array << endl;
    array.neirongpaixu();
    cout << "ContentSorted: " << array << endl;
    array.changdupaixu();
    cout << "LengthSorted: " << array << endl;
}