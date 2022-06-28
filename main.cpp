#include <iostream>
#include <vector> 
#include <algorithm>

using namespace std;

float combine(float a, float b, int way)
{
    if (way == 0)
    {
       return a + b;
    }
    if(way == 1)
    {
        return a - b;
    }
    if(way == 2)
    {
        return b - a;
    }
    if(way == 3)
    {
        return a * b;
    }
    if(way == 4)
    {
        return a / b;
    }
    if(way == 5)
    {
        return b / a;
    }
}

struct COMBINE
{
    float a;
    float b;
    int way;
};
struct CAL
{
    int id;
    int pre_id;
    COMBINE combine;
    vector<float> num;
};
vector<CAL> cals;
vector<COMBINE> combs;
int prob_num = 0;

void print(COMBINE comb)
{
    auto x = comb.way;
    string str;
    auto a = abs(comb.a - (int)comb.a) < 0.00001 ? int(comb.a) : comb.a;
    auto b = abs(comb.b - (int)comb.b) < 0.00001 ? int(comb.b) : comb.b;
    auto comb_result = combine(comb.a, comb.b, comb.way);
    auto result = abs(comb_result- (int)comb_result) < 0.00001 ? int(comb_result) : comb_result;
    
    if(x != 2 && x != 5)
    {
        cout << a;
        if (x == 0)
        {
           cout << " + ";
        }
        if(x == 1)
        {
            cout << " - ";
        }
        if(x == 3)
        {
            cout << " * ";
        }
        if(x == 4)
        {
            cout << " / ";
        }
        cout << b;
        cout << " = ";
    }
    else
    {
        cout << b;
        if(x == 2)
        {
            cout << " - ";
        }
        
        if(x == 5)
        {
            cout << " / ";
        }
        cout << a;
        cout << " = ";
    }
    cout << result;
    
    cout << str;
    cout << "\n"; 
}

void check(vector<float> num, int pre_id)
{
    for(int n = 0; n < num.size(); n++)
    {
        for(int m = n; m < num.size(); m++)
        {
            
            if(num.size() == 1)
            {
                if(abs(num[0] - 24) <0.00001)
                {
                    while(true)
                    {
                        auto itr = 
                            find_if(
                                cals.begin(), 
                                cals.end(), 
                                [pre_id](const CAL& cal)->bool {
                                    return cal.id == pre_id; 
                                }
                            );
                        pre_id = itr->pre_id;
                        if(pre_id < 0)
                        {
                            break;
                        }
                        combs.emplace_back(itr->combine);
                    }
                    
                    reverse(combs.begin(), combs.end());
                    for(auto comb : combs)
                    {
                        print(comb);
                    }
                    combs.clear();
                    prob_num++;
                    cout << "\n";
                    
                }
                return;
            }
            
            if(n == m)
            {
                continue;
            }
            
            
            for(int x = 0; x < 6; x++)
            {
                if((num[n] == num[m]) && (x == 2 || x == 5))
                {
                    continue;
                }
                
                float combineResult = combine(num[n], num[m], x);
                
                vector<float> temp;
                temp.emplace_back(combineResult);
                
                for(int z = 0; z < num.size();z++)
                {
                    if(z != n && z != m)
                    {
                        temp.emplace_back(num[z]);
                    }
                }
                
                auto itr = 
                    find_if(
                        cals.begin(), 
                        cals.end(), 
                        [temp, x, n, m, num](const CAL& cal)->bool {
                            return cal.num == temp && cal.combine.a == num[n] && cal.combine.b == num[m] && cal.combine.way == x; 
                        }
                    );
                if(itr  == cals.end())
                {
                    COMBINE newCombine = {num[n], num[m], x};
                    int id = cals.size();
                    CAL newCal = {id, pre_id, newCombine, temp};
                    cals.emplace_back(newCal);
                    
                        
                    check(temp, id);
                }
            }
        }
    }
}

int main() {
    int a,b,c,d;
    cin >> a;
    cin >> b;
    cin >> c;
    cin >> d;
    
    float org_data[4] = {a,b,c,d};
    
    vector<float> num(org_data, end(org_data));
    
    CAL newCal = {0, -1, {}, num};
    cals.emplace_back(newCal);
    
    check(num, 0);
    
    cout << prob_num;
    cout << " possible way to get 24\n";
    if(!prob_num)
    {
        cout<< "Can't get 24!!! \n";
    }

    return 0;
}


