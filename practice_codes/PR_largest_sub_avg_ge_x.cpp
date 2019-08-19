#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

const int k = 0;
int n, avg_lim;
int pre[100005], minIdx[100005];
vector<pair<int, int> > pres;

void read()
{
    cin>>n>>avg_lim;
    pres.resize(n);

    for(int i = 0;i < n;i++)
    {
        cin>>pre[i];
        pre[i] -= avg_lim;

        if(i)
            pre[i] += pre[i - 1];
        pres[i] = {pre[i], i};
    }

    sort(pres.begin(), pres.end());
    minIdx[0] = pres[0].second; 
    for(int i = 1;i < n;i++)
        minIdx[i] = min(minIdx[i - 1], pres[i].second);
}

// Find largest value less than or equal to x
// in pres vector
int b_search(int x)
{
    if(pres[n - 1].first <= x)
        return minIdx[n - 1];

    int low = 0, high = n - 1, mid;
    mid = (low + high) / 2;

    while(low <= high)
    {
        if(mid < n - 1 && pres[mid].first <= x && pres[mid + 1].first > x)
            return minIdx[mid];
        else if(mid < n - 1 && pres[mid + 1].first <= x)
            low = mid + 1;
        else
            high = mid - 1;
        mid = (low + high) / 2;
    }

    return -1;
}

void solve()
{
    int ans = 0, idx;
    for(int i = 0;i < n;i++)
    {
        if(pre[i] >= k)
        {
            ans = max(ans, i + 1);
            continue;
        }

        idx = b_search(pre[i] - k);
        if(idx == -1 || idx >= i)
            continue;

        ans = max(ans, i - idx);
    }

    cout<<ans<<"\n";
}

int main()
{
    read();
    solve();
    return 0;
}