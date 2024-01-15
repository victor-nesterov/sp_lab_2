// ������� 3

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct TransitionFunction
{
public:
    int s; // �� ������ ���������
    char a; // �� ������ �������
    int s_bar; // s' - � ����� ���������
    TransitionFunction() {}
    TransitionFunction(int S, char A, int S_BAR)
    {
        s = S;
        a = A;
        s_bar = S_BAR;
    }
};

int main()
{
    // ��������� ����:
    ifstream fin;
    fin.open("C:\\Users\\Victor\\source\\repos\\Lab1\\input.txt");
    if (!fin)
    {
        cout << "Cannot open the file" << endl;
        return 1;
    }
    // ������ �����:
    int A, S, s0;
    int F_count; // ���-�� ��������� ���������
    fin >> A >> S >> s0 >> F_count;
    vector<int> F(F_count);
    for (int i = 0; i < F_count; ++i) // ���� ��������� ���������
        fin >> F[i];
    int input1, input3;
    char input2;
    vector<TransitionFunction> f(0);
    while (fin >> input1 >> input2 >> input3) // ���� ������� ��������
        f.push_back(TransitionFunction(input1, input2, input3));
    // ������ �����:
    cout << "Enter word: ";
    string word;
    cin >> word;
    cout << endl;
    // ���������� ������:
    vector<int> current_state(1, s0);
    vector<vector<int>> states_log(1, vector<int>(1, s0));
    for (auto c : word) // ��� �� �������� ����� (c - ������)
    {
        vector<int> tmp_state(0);
        vector<vector<int>> tmp_log(0);
        for (int i = 0; i < current_state.size(); ++i) // ��� �� ���� ������� "������" ��������� (cs - ���������)
        {
            char cs = current_state[i];
            for (auto tf : f) // ������� � ����� ��������� ������� ����� �������
            {
                if (tf.s == cs && tf.a == c)
                {
                    tmp_state.push_back(tf.s_bar);
                    vector<int> log = states_log[i];
                    log.push_back(tf.s_bar);
                    tmp_log.push_back(log);

                    cout << s0;
                    for (int u = 1; u < log.size(); ++u)
                        cout << " -(" << word[u - 1] << ")-> " << log[u];

                    if (log.size() == word.size() + 1) // ���� ��� ��������� ���
                    {
                        bool final = false;
                        for (auto F_state : F) // ���������� �� ���� F_state
                        {
                            if (F_state == log[word.size()]) // ���� �������� ��������� - ���������
                            {
                                final = true;
                                break;
                            }
                        }
                        if (final)
                            cout << "  (final state)";
                        else
                            cout << "  (not a final state)";
                    }

                    cout << endl;
                }
            }
        }
        current_state = tmp_state;
        states_log = tmp_log;
        cout << endl;
    }
    return 0;
}