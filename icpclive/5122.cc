// precomputation

#include <iostream>
#include <iomanip>

using namespace std;

typedef long long ll;
ll fib[93] = {0,1LL,1LL,2LL,3LL,5LL,8LL,13LL,21LL,34LL,55LL,89LL,144LL,233LL,377LL,610LL,987LL,1597LL,2584LL,4181LL,6765LL,10946LL,17711LL,28657LL,46368LL,75025LL,121393LL,196418LL,317811LL,514229LL,832040LL,1346269LL,2178309LL,3524578LL,5702887LL,9227465LL,14930352LL,24157817LL,39088169LL,63245986LL,102334155LL,165580141LL,267914296LL,433494437LL,701408733LL,1134903170LL,1836311903LL,2971215073LL,4807526976LL,7778742049LL,12586269025LL,20365011074LL,32951280099LL,53316291173LL,86267571272LL,139583862445LL,225851433717LL,365435296162LL,591286729879LL,956722026041LL,1548008755920LL,2504730781961LL,4052739537881LL,6557470319842LL,10610209857723LL,17167680177565LL,27777890035288LL,44945570212853LL,72723460248141LL,117669030460994LL,190392490709135LL,308061521170129LL,498454011879264LL,806515533049393LL,1304969544928657LL,2111485077978050LL,3416454622906707LL,5527939700884757LL,8944394323791464LL,14472334024676221LL,23416728348467685LL,37889062373143906LL,61305790721611591LL,99194853094755497LL,160500643816367088LL,259695496911122585LL,420196140727489673LL,679891637638612258LL,1100087778366101931LL,1779979416004714189LL,2880067194370816120LL,4660046610375530309LL,7540113804746346429LL};
string lg[93] = {"lg does not exist", "lg is 0.000000", "lg is 0.000000", "lg is 1.000000", "lg is 1.584963", "lg is 2.321928", "lg is 3.000000", "lg is 3.700440", "lg is 4.392317", "lg is 5.087463", "lg is 5.781360", "lg is 6.475733", "lg is 7.169925", "lg is 7.864186", "lg is 8.558421", "lg is 9.252665", "lg is 9.946906", "lg is 10.641149", "lg is 11.335390", "lg is 12.029632", "lg is 12.723874", "lg is 13.418116", "lg is 14.112358", "lg is 14.806600", "lg is 15.500842", "lg is 16.195084", "lg is 16.889326", "lg is 17.583568", "lg is 18.277810", "lg is 18.972051", "lg is 19.666293", "lg is 20.360535", "lg is 21.054777", "lg is 21.749019", "lg is 22.443261", "lg is 23.137503", "lg is 23.831745", "lg is 24.525987", "lg is 25.220229", "lg is 25.914471", "lg is 26.608712", "lg is 27.302954", "lg is 27.997196", "lg is 28.691438", "lg is 29.385680", "lg is 30.079922", "lg is 30.774164", "lg is 31.468406", "lg is 32.162648", "lg is 32.856890", "lg is 33.551132", "lg is 34.245374", "lg is 34.939615", "lg is 35.633857", "lg is 36.328099", "lg is 37.022341", "lg is 37.716583", "lg is 38.410825", "lg is 39.105067", "lg is 39.799309", "lg is 40.493551", "lg is 41.187793", "lg is 41.882035", "lg is 42.576277", "lg is 43.270518", "lg is 43.964760", "lg is 44.659002", "lg is 45.353244", "lg is 46.047486", "lg is 46.741728", "lg is 47.435970", "lg is 48.130212", "lg is 48.824454", "lg is 49.518696", "lg is 50.212938", "lg is 50.907179", "lg is 51.601421", "lg is 52.295663", "lg is 52.989905", "lg is 53.684147", "lg is 54.378389", "lg is 55.072631", "lg is 55.766873", "lg is 56.461115", "lg is 57.155357", "lg is 57.849599", "lg is 58.543841", "lg is 59.238082", "lg is 59.932324", "lg is 60.626566", "lg is 61.320808", "lg is 62.015050", "lg is 62.709292"};
string factors[93] = {"No prime factors","No prime factors","No prime factors","Prime factors: 2","Prime factors: 3","Prime factors: 5","Prime factors: 2 2 2","Prime factors: 13","Prime factors: 3 7","Prime factors: 2 17","Prime factors: 5 11","Prime factors: 89","Prime factors: 2 2 2 2 3 3","Prime factors: 233","Prime factors: 13 29","Prime factors: 2 5 61","Prime factors: 3 7 47","Prime factors: 1597","Prime factors: 2 2 2 17 19","Prime factors: 37 113","Prime factors: 3 5 11 41","Prime factors: 2 13 421","Prime factors: 89 199","Prime factors: 28657","Prime factors: 2 2 2 2 2 3 3 7 23","Prime factors: 5 5 3001","Prime factors: 233 521","Prime factors: 2 17 53 109","Prime factors: 3 13 29 281","Prime factors: 514229","Prime factors: 2 2 2 5 11 31 61","Prime factors: 557 2417","Prime factors: 3 7 47 2207","Prime factors: 2 89 19801","Prime factors: 1597 3571","Prime factors: 5 13 141961","Prime factors: 2 2 2 2 3 3 3 17 19 107","Prime factors: 73 149 2221","Prime factors: 37 113 9349","Prime factors: 2 233 135721","Prime factors: 3 5 7 11 41 2161","Prime factors: 2789 59369","Prime factors: 2 2 2 13 29 211 421","Prime factors: 433494437","Prime factors: 3 43 89 199 307","Prime factors: 2 5 17 61 109441","Prime factors: 139 461 28657","Prime factors: 2971215073","Prime factors: 2 2 2 2 2 2 3 3 7 23 47 1103","Prime factors: 13 97 6168709","Prime factors: 5 5 11 101 151 3001","Prime factors: 2 1597 6376021","Prime factors: 3 233 521 90481","Prime factors: 953 55945741","Prime factors: 2 2 2 17 19 53 109 5779","Prime factors: 5 89 661 474541","Prime factors: 3 7 7 13 29 281 14503","Prime factors: 2 37 113 797 54833","Prime factors: 59 19489 514229","Prime factors: 353 2710260697","Prime factors: 2 2 2 2 3 3 5 11 31 41 61 2521","Prime factors: 4513 555003497","Prime factors: 557 2417 3010349","Prime factors: 2 13 17 421 35239681","Prime factors: 3 7 47 1087 2207 4481","Prime factors: 5 233 14736206161","Prime factors: 2 2 2 89 199 9901 19801","Prime factors: 269 116849 1429913","Prime factors: 3 67 1597 3571 63443","Prime factors: 2 137 829 18077 28657","Prime factors: 5 11 13 29 71 911 141961","Prime factors: 6673 46165371073","Prime factors: 2 2 2 2 2 3 3 3 7 17 19 23 107 103681","Prime factors: 9375829 86020717","Prime factors: 73 149 2221 54018521","Prime factors: 2 5 5 61 3001 230686501","Prime factors: 3 37 113 9349 29134601","Prime factors: 13 89 988681 4832521","Prime factors: 2 2 2 79 233 521 859 135721","Prime factors: 157 92180471494753","Prime factors: 3 5 7 11 41 47 1601 2161 3041","Prime factors: 2 17 53 109 2269 4373 19441","Prime factors: 2789 59369 370248451","Prime factors: 99194853094755497","Prime factors: 2 2 2 2 3 3 13 29 83 211 281 421 1427","Prime factors: 5 1597 9521 3415914041","Prime factors: 6709 144481 433494437","Prime factors: 2 173 514229 3821263937","Prime factors: 3 7 43 89 199 263 307 881 967","Prime factors: 1069 1665088321800481","Prime factors: 2 2 2 5 11 17 19 31 61 181 541 109441","Prime factors: 13 13 233 741469 159607993","Prime factors: 3 139 461 4969 28657 275449"};

int main(void)
{
  ll a, b;
  bool first = true;
  while (cin >> hex >> a >> b && (a < b)) {
    if (!first) cout << endl;
    cout << "Range " << a << " to " << b << ":" << endl;
    bool printed = false;
    for (int n = 0; n < 93; n++) {
      if (a <= fib[n] && fib[n] <= b) {
	cout << "Fib(" << n << ") = " << fib[n] << ", " << lg[n] << endl;
	cout << factors[n] << endl;
	printed = true;
      }
    }
    if (!printed) {
      cout << "No Fibonacci numbers in the range" << endl;
    }
    first = false;
  }
  cout << endl;
  return 0;
}
