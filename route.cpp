#include <iostream>
#include <cstdlib>
using namespace std;

class route
{
    int *r, n; // r – массив, представляющий маршрут; n – количество городов
    
    public:
    route(int n = 0); // создает начальную перестановку по возрастанию
    route(const route &m); // конструктор копирования
    route & operator = (const route &m); // операция присваивания
    ~route() // деструктор
    {
        if (r)
        {
            delete []r; 
            r = NULL;
        }
    }
    int getN();
    int route_price(int **matrix); // вычисляет стоимость маршрута по матрице стоимости
    bool next_route(); // вычисляет следующий маршрут, используя алгоритм Дейкстры
    friend ostream & operator << (ostream&, const route&); // вывод маршрута
};

route :: route (int n)
{
    this -> n = n;
    r = new int [n];
    for (int i = 0; i < n; i++)
    {
        r[i] = i + 1;
    }
}

route :: route (const route &m)
{
    n = m.n;
    r = new int [n];
    for (int i = 0; i < n; i++)
    {
        r[i] = m.r[i];
    }
}

route & route :: operator = (const route &m)
{
    if (this != &m) //m = m
    {
        for (int i = 0; i < n; i ++)
        {
            r[i] = m.r[i];
        }
    }
    
    return *this;
}

int route :: getN ()
{
    return n;
}

int route :: route_price (int **matrix)
{
    int st = 0;
    for (int i = 0; i < n-1; i++) // 1234: 1-2 2-3 3-4 4-1
    {
        st = st + matrix [r[i] - 1][r[i+1] -1];
    }
    st = st + matrix [r[n-1] - 1][r[0] - 1];
    return st;
}

bool route :: next_route()
{
    //Поиск максимального i
    int i;
    for (i = n-2; i > 0; i--)
    {
        if (r[i] < r[i+1])
        {
            break;
        }
    }

    //Выход из функции, если i не нашлось 
    if (i == 0)
    {
        //cout << "There is no next permutation" << endl;
        return false;
    }

    //Поиск максимального j, замена r[i] и r[j]
    for (int j = n-1; j > i; j--)
    {
        if (r[i] < r[j])
        {
            int t = r[i];
            r[i] = r[j];
            r[j] = t;
            break;
        }        
    }

    //Упорядочивание хвоста
    
    int l = n-1;
    
    i++;
    for ( ; i < l; i++, l--)   
    {
        int t = r[i];
        r[i] = r[l];
        r[l] = t;
    }
    
    return true;
}

ostream & operator << (ostream &print, const route &m)
{
    for (int i = 0; i < m.n; i++)
    {
        print << m.r[i];
    }

    return print;
}

int main ()
{
    route travel (4);
    int cities = travel.getN();
    

    int **matrix = new int * [cities];
    for (int i = 0; i < cities; i++)
    {
        matrix[i] = new int [cities];
    }

    for (int i = 0; i < cities; i++)
    {
        for (int j = 0; j < cities; j++)
        {
            cin >> matrix [i][j]; 
        }
    } 

    int min = travel.route_price (matrix), local_min;  
    route min_travel = travel; 

    while (travel.next_route() != false)
    {
        local_min = travel.route_price(matrix); 
        
        if (min > local_min)
        {
            min = local_min;
            min_travel = travel;
        }    

        cout << local_min << "    " << travel << endl;    
    }

    cout << "----------" << endl;
    cout << min << endl;
    cout << min_travel << endl;

    for (int i = 0; i < cities; i++)
    {
        delete [] matrix[i];
    } 
    delete [] matrix;

    return 0;
}