// Вариант 3

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct TransitionFunction
{
public:
    int s; // Из какого состояния
    char a; // По какому символу
    int s_bar; // s' - В какое состояние
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
    // Открываем файл:
    ifstream fin;
    fin.open("C:\\Users\\Victor\\source\\repos\\Lab1\\input.txt");
    if (!fin)
    {
        cout << "Cannot open the file" << endl;
        return 1;
    }
    // Читаем текст:
    int A, S, s0;
    int F_count; // кол-во финальных состояний
    fin >> A >> S >> s0 >> F_count;
    vector<int> F(F_count);
    for (int i = 0; i < F_count; ++i) // ввод финальных состояний
        fin >> F[i];
    int input1, input3;
    char input2;
    vector<TransitionFunction> f(0);
    while (fin >> input1 >> input2 >> input3) // ввод функции перехода
        f.push_back(TransitionFunction(input1, input2, input3));
    // Вводим слово:
    cout << "Enter word: ";
    string word;
    cin >> word;
    cout << endl;
    // Моделируем работу:
    vector<int> current_state(1, s0);
    vector<vector<int>> states_log(1, vector<int>(1, s0));
    for (auto c : word) // идём по символам слова (c - символ)
    {
        vector<int> tmp_state(0);
        vector<vector<int>> tmp_log(0);
        for (int i = 0; i < current_state.size(); ++i) // идём по всем текущим "веткам" состояний (cs - состояние)
        {
            char cs = current_state[i];
            for (auto tf : f) // смотрим в какие состояние автомат может перейти
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

                    if (log.size() == word.size() + 1) // если уже последний шаг
                    {
                        bool final = false;
                        for (auto F_state : F) // проходимся по всем F_state
                        {
                            if (F_state == log[word.size()]) // если конечное состояние - финальное
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