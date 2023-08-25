#include"BigInt.h"
#include <chrono>

using namespace std;
BigInt powerMod(BigInt x, BigInt y, BigInt p)
{
    BigInt res = BigInt("1");     // Initialize result

    x = x % p; // Update x if it is more than or
    // equal to p

    if (x == BigInt("0")) return BigInt("0"); // In case x is divisible by p;

    while (y > BigInt("0"))
    {
        // If y is odd, multiply x with result
        if (y % BigInt("2") != BigInt("0"))
            res = (res * x) % p;

        // y must be even now
        y /= BigInt("2");
        x = (x * x) % p;
    }
    return res;
}
BigInt encrypt(BigInt x, BigInt e, BigInt n) {
    return powerMod(x, e, n);
}

BigInt decrypt(BigInt c, BigInt d, BigInt n) {
    return powerMod(c, d, n);
}

void phi_n_d_cal(const BigInt& p, const BigInt& q, const BigInt& e, BigInt& phi, BigInt& n, BigInt& d) {
    phi = (p - BigInt("1")) * (q - BigInt("1"));
    n = p * q;
    d = BigInt::inverseModulo(e, phi);
}

void fileEncryption(const BigInt& p, const BigInt& q, const BigInt& e) {
    string plaintext;
    vector<string> encode, encrypt_list;
    BigInt phi, n, d;
    BigInt en;
    
    //MA HOA TAP TIN
    //tinh phi, n, d
    phi_n_d_cal(p, q, e, phi, n, d);

    //Nhap data
    string des;
    cin.ignore();
    cout << "Nhap duong dan file plaintext:" << endl;
    getline(cin, des);
    ifstream ifs_Encode(des);
    if (ifs_Encode.fail())
    {
        cout << "Nhap sai duong dan!" << endl;
        return;
    }
    //Xuat du lieu
    cin.ignore();
    cout << "Nhap duong dan file ciphertext" << endl;
    getline(cin, des);
    ofstream ofs_Encode(des);
    if (ofs_Encode.fail())
    {
        cout << "Nhap sai duong dan!" << std::endl;
        return;
    }
    while (!ifs_Encode.eof()) {
        plaintext = "";
        getline(ifs_Encode, plaintext);

        //chuyen van ban chu ve so
        cout << endl << "Plaintext: " << plaintext << endl;
        for (int i = 0; i < plaintext.size(); i++)
        {
            encode.push_back(to_string(int(plaintext.at(i))));
        }

        //Ma hoa 
        //Luu nhung ki tu duoc ma hoa vao list
        for (int i = 0; i < encode.size(); i++)
        {
            en = encrypt(encode[i], e, n);
            encrypt_list.push_back(en.getNum());
        }

        //Xuat du lieu da duoc ma hoa 
        for (int i = 0; i < encrypt_list.size(); i++)
        {
            ofs_Encode << encrypt_list[i] << " ";
            cout << encrypt_list[i] << " ";
        }
        if (!ifs_Encode.eof())
            ofs_Encode << endl;
        encode.clear();
        encrypt_list.clear();
    }
    ifs_Encode.close();
    ofs_Encode.close();
}

void fileDecryption(const BigInt& p, const BigInt& q, const BigInt& e) {
    string ciphertext;
    vector<string> encode, encrypt_list, decrypt_list;
    BigInt phi, n, d;
    BigInt de;

    //GIAI MA TAP TIN
    //tinh phi, n, d
    phi_n_d_cal(p, q, e, phi, n, d);
    //Doc du lieu ma hoa
    string des;
    cin.ignore();
    cout << "Nhap duong dan file ciphertext:" << endl;
    getline(cin, des);
    ifstream ifs_Decode(des);
    
    //ifstream ifs_Decode("D:/HCMUS/3/1/NMMHMM/RSA/RSA/data/Cyphertext.txt");
    if (ifs_Decode.fail())
    {
        cout << "Nhap sai duong dan!" << std::endl;
        return;
    }

    //Xuat du lieu da duocgiai ma 
    cin.ignore();
    cout << "Nhap duong dan file plaintext:" << endl;
    getline(cin, des);
    ofstream ofs_Decode(des);
    if (ofs_Decode.fail())
    {
        cout << "Nhap sai duong dan!" << std::endl;
        return;
    }
    while (!ifs_Decode.eof()) {
        ciphertext = "";
        string temp;
        getline(ifs_Decode, temp);
        istringstream stream(temp);
        while (getline(stream, ciphertext, ' '))
        {
            encrypt_list.push_back(ciphertext);
        }
        

        //Giai ma ciphertext 
        for (int i = 0; i < encrypt_list.size(); i++)
        {
            de = decrypt(encrypt_list[i], d, n);
            decrypt_list.push_back(de.getNum());

        }

        for (int i = 0; i < decrypt_list.size(); i++)
        {
            ofs_Decode << char(stoi(decrypt_list[i]));
        }
        if (!ifs_Decode.eof())
            ofs_Decode << endl;
        encrypt_list.clear();
        decrypt_list.clear();
    }
    ifs_Decode.close();
    ofs_Decode.close();
}

int main()
{
    //Sinh khóa
    BigInt p, q, e;
    int choice1 = 0;
    cout << "_____MENU_____" << endl;
    cout << "1. Random RSA key" << endl;
    cout << "2. Input RSA key p, q, e" << endl;
    cout << "0. Exit" << endl;
    cout << "--------------" << endl;
    cout << "Choice: ";
    do {
        cin >> choice1;
    } while (choice1 != 0 && choice1 != 1 && choice1 != 2);

    if (choice1 == 0)
        return 0;
    else if (choice1 == 1) {
        do {
            p = BigInt(p.randomString(3));
            e = BigInt(e.randomString(2));
            q = BigInt(q.randomString(3));
            if (p.isPrime() && q.isPrime() && e.isPrime() && p != q)
                break;
        } while (1);
    }
    else if (choice1 == 2) {
        do {

            cout << "Nhap p: "; cin >> p;
            cout << "Nhap q: "; cin >> q;
            cout << "Nhap e: "; cin >> e;

            if (p.isPrime() && q.isPrime() && e.isPrime() && p != q)
                break;
            else {
                cout << "wrong input ";
            }
        } while (1);
    }

    int choice2 = 0;
    
    do {
        system("cls");
        cout << "p = " << p << endl;
        cout << "q = " << q << endl;
        cout << "e = " << e << endl;
        cout << "--------------" << endl << endl;


        cout << "_____MENU_____" << endl;
        cout << "1. File encryption" << endl;
        cout << "2. File decryption" << endl;
        cout << "0. Exit" << endl;
        cout << "--------------" << endl;
        cout << "Choice: ";
        do {
            cin >> choice2;
        } while (choice2 != 0 && choice2 != 1 && choice2 != 2);
        cout << endl;

        if (choice2 == 0)
            return 0;
        else if (choice2 == 1)
            fileEncryption(p, q, e);
        else if (choice2 == 2)
            fileDecryption(p, q, e);

        system("pause");
    } while (choice2 != 0);

    return 0;
}