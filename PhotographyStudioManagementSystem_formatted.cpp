#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iomanip>
using namespace std;
string field(string s) {
    replace(s.begin(),s.end(),'^',' ');
    replace(s.begin(),s.end(),'\n',' ');
    replace(s.begin(),s.end(),'\r',' ');
    return s;
}
string input(const string& p) {
    cout<<p;
    string s;
    getline(cin,s);
    return field(s);
}
int integer(const string& p) {
    while(true) {
        string s=input(p);
        stringstream q(s);
        int n;
        char c;
        if((q>>n)&&!(q>>c))return n;
        cout<<"Enter a whole number.\n";
    }
}
double number(const string& p) {
    while(true) {
        string s=input(p);
        stringstream q(s);
        double n;
        char c;
        if((q>>n)&&!(q>>c)&&n>=0)return n;
        cout<<"Enter a non-negative number.\n";
    }
}
bool pi(const string&s,int&n) {
    stringstream q(s);
    char c;
    return (q>>n)&&!(q>>c);
}
bool pd(const string&s,double&n) {
    stringstream q(s);
    char c;
    return (q>>n)&&!(q>>c);
}
vector<string> split(const string&s) {
    vector<string>v;
    string x;
    stringstream q(s);
    while(getline(q,x,'^'))v.push_back(x);
    if(!s.empty()&&s.back()=='^')v.push_back("");
    return v;
}
bool dateOK(const string&s) {
    if(s.size()!=10||s[4]!='-'||s[7]!='-')return false;
    int y,m,d;
    if(!pi(s.substr(0,4),y)||!pi(s.substr(5,2),m)||!pi(s.substr(8,2),d)||y<1900||m<1||m>12)return false;
    int ds[]= {
        31,28,31,30,31,30,31,31,30,31,30,31
    }
    ;
    if(y%400==0||(y%4==0&&y%100!=0))ds[1]=29;
    return d>0&&d<=ds[m-1];
}
class Person {
    protected: int id;
    string name,phone,email;
    public:
    Person():id(0) {
    }
    Person(int i,string n,string p,string e):id(i),name(n),phone(p),email(e) {
    }
    virtual ~Person() {
    }
    int getId()const {
        return id;
    }
    string getName()const {
        return name;
    }
    string getPhone()const {
        return phone;
    }
    string getEmail()const {
        return email;
    }
    void setName(string x) {
        name=x;
    }
    void setPhone(string x) {
        phone=x;
    }
    void setEmail(string x) {
        email=x;
    }
    virtual string role()const=0;
    virtual void display()const {
        cout<<id<<" | "<<name<<" | "<<phone<<" | "<<email;
    }
}
;
class Customer:public Person {
    public: Customer() {
    }
    Customer(int i,string n,string p,string e):Person(i,n,p,e) {
    }
    ~Customer()override {
    }
    string role()const override {
        return "Customer";
    }
    void display()const override {
        Person::display();
        cout<<" | Customer\n";
    }
    string save()const {
        return to_string(id)+"^"+name+"^"+phone+"^"+email;
    }
}
;
class Photographer:public Person {
    string specialty;
    double rate;
    public: Photographer():rate(0) {
    }
    Photographer(int i,string n,string p,string e,string s,double r):Person(i,n,p,e),specialty(s),rate(r) {
    }
    ~Photographer()override {
    }
    string role()const override {
        return "Photographer";
    }
    string getSpecialty()const {
        return specialty;
    }
    double getRate()const {
        return rate;
    }
    void setSpecialty(string x) {
        specialty=x;
    }
    void setRate(double x) {
        rate=x;
    }
    void display()const override {
        Person::display();
        cout<<" | "<<specialty<<" | Rs."<<rate<<"\n";
    }
    string save()const {
        return to_string(id)+"^"+name+"^"+phone+"^"+email+"^"+specialty+"^"+to_string(rate);
    }
}
;
class Package {
    protected:int id;
    string name;
    double price;
    int hours;
    public: Package():id(0),price(0),hours(1) {
    }
    Package(int i,string n,double p,int h):id(i),name(n),price(p),hours(h) {
    }
    virtual ~Package() {
    }
    int getId()const {
        return id;
    }
    string getName()const {
        return name;
    }
    double getPrice()const {
        return price;
    }
    int getHours()const {
        return hours;
    }
    void setName(string x) {
        name=x;
    }
    void setPrice(double x) {
        price=x;
    }
    void setHours(int x) {
        hours=x;
    }
    virtual string type()const {
        return "Standard";
    }
    virtual double total()const {
        return price;
    }
    virtual void display()const {
        cout<<id<<" | "<<name<<" | "<<type()<<" | "<<hours<<" hours | Rs."<<fixed<<setprecision(2)<<total()<<"\n";
    }
    virtual string save()const {
        return to_string(id)+"^"+name+"^"+to_string(price)+"^"+to_string(hours)+"^S^0";
    }
}
;
class PremiumPackage:public Package {
    double extra;
    public: PremiumPackage():extra(0) {
    }
    PremiumPackage(int i,string n,double p,int h,double e):Package(i,n,p,h),extra(e) {
    }
    ~PremiumPackage()override {
    }
    string type()const override {
        return "Premium";
    }
    double total()const override {
        return price+extra;
    }
    double getExtra()const {
        return extra;
    }
    void setExtra(double x) {
        extra=x;
    }
    void display()const override {
        Package::display();
        cout<<"   Premium charge: Rs."<<extra<<"\n";
    }
    string save()const override {
        return to_string(id)+"^"+name+"^"+to_string(price)+"^"+to_string(hours)+"^P^"+to_string(extra);
    }
}
;
class Booking {
    int id,cid,pid,pkgid;
    string date,event,status;
    double amount;
    public:
    Booking():id(0),cid(0),pid(0),pkgid(0),amount(0),status("Confirmed") {
    }
    Booking(int i,int c,int p,int k,string d,string e,double a,string s="Confirmed"):id(i),cid(c),pid(p),pkgid(k),date(d),event(e),status(s),amount(a) {
    }
    ~Booking() {
    }
    int getId()const {
        return id;
    }
    int getCustomer()const {
        return cid;
    }
    int getPhotographer()const {
        return pid;
    }
    int getPackage()const {
        return pkgid;
    }
    string getDate()const {
        return date;
    }
    string getStatus()const {
        return status;
    }
    double getAmount()const {
        return amount;
    }
    void setDate(string x) {
        date=x;
    }
    void setEvent(string x) {
        event=x;
    }
    void setPhotographer(int x) {
        pid=x;
    }
    void setPackage(int x) {
        pkgid=x;
    }
    void setAmount(double x) {
        amount=x;
    }
    void setStatus(string x) {
        status=x;
    }
    void display()const {
        cout<<id<<" | C:"<<cid<<" | Photographer:"<<pid<<" | Package:"<<pkgid<<" | "<<date<<" | "<<event<<" | Rs."<<amount<<" | "<<status<<"\n";
    }
    string save()const {
        return to_string(id)+"^"+to_string(cid)+"^"+to_string(pid)+"^"+to_string(pkgid)+"^"+date+"^"+event+"^"+to_string(amount)+"^"+status;
    }
}
;
class StudioSystem {
    vector<Customer> customers;
    vector<Photographer> photographers;
    vector<unique_ptr<Package>> packages;
    vector<Booking> bookings;
    int nc=1,np=1,nk=1,nb=1;
    Customer* fc(int id) {
        for(auto&x:customers)if(x.getId()==id)return &x;
        return nullptr;
    }
    Photographer* fp(int id) {
        for(auto&x:photographers)if(x.getId()==id)return &x;
        return nullptr;
    }
    Package* fk(int id) {
        for(auto&x:packages)if(x->getId()==id)return x.get();
        return nullptr;
    }
    Booking* fb(int id) {
        for(auto&x:bookings)if(x.getId()==id)return &x;
        return nullptr;
    }
    bool phoneUsed(string p,int except=-1)const {
        for(auto&x:customers)if(x.getPhone()==p&&x.getId()!=except)return true;
        return false;
    }
    bool busy(int pid,string d,int except=-1)const {
        for(auto&b:bookings)if(b.getId()!=except&&b.getPhotographer()==pid&&b.getDate()==d&&b.getStatus()!="Cancelled")return true;
        return false;
    }
    void saveFile(string fn,const vector<string>& rows)const {
        ofstream f(fn);
        for(auto&s:rows)f<<s<<"\n";
    }
    void saveAll()const {
        vector<string>v;
        for(auto&x:customers)v.push_back(x.save());
        saveFile("customers.txt",v);
        v.clear();
        for(auto&x:photographers)v.push_back(x.save());
        saveFile("photographers.txt",v);
        v.clear();
        for(auto&x:packages)v.push_back(x->save());
        saveFile("packages.txt",v);
        v.clear();
        for(auto&x:bookings)v.push_back(x.save());
        saveFile("bookings.txt",v);
    }
    void load() {
        string s;
        int i,a,b,c,h;
        double d,e;
        ifstream f("customers.txt");
        while(getline(f,s)) {
            auto v=split(s);
            if(v.size()==4&&pi(v[0],i)) {
                customers.emplace_back(i,v[1],v[2],v[3]);
                nc=max(nc,i+1);
            }
        }
        f.close();
        f.open("photographers.txt");
        while(getline(f,s)) {
            auto v=split(s);
            if(v.size()==6&&pi(v[0],i)&&pd(v[5],d)) {
                photographers.emplace_back(i,v[1],v[2],v[3],v[4],d);
                np=max(np,i+1);
            }
        }
        f.close();
        f.open("packages.txt");
        while(getline(f,s)) {
            auto v=split(s);
            if(v.size()==6&&pi(v[0],i)&&pd(v[2],d)&&pi(v[3],h)&&pd(v[5],e)) {
                if(v[4]=="P")packages.emplace_back(new PremiumPackage(i,v[1],d,h,e));
                else packages.emplace_back(new Package(i,v[1],d,h));
                nk=max(nk,i+1);
            }
        }
        f.close();
        f.open("bookings.txt");
        while(getline(f,s)) {
            auto v=split(s);
            if(v.size()==8&&pi(v[0],i)&&pi(v[1],a)&&pi(v[2],b)&&pi(v[3],c)&&pd(v[6],d)) {
                bookings.emplace_back(i,a,b,c,v[4],v[5],d,v[7]);
                nb=max(nb,i+1);
            }
        }
        if(photographers.empty())photographers.emplace_back(np++,"Aarav Patel","9876543210","aarav@example.com","Wedding",8000);
        if(packages.empty()) {
            packages.emplace_back(new Package(nk++,"Basic Portrait",2500,2));
            packages.emplace_back(new PremiumPackage(nk++,"Wedding Premium",15000,6,3000));
        }
        saveAll();
    }
    void listC()const {
        for(auto&x:customers)x.display();
        if(customers.empty())cout<<"No customers.\n";
    }
    void listP()const {
        for(auto&x:photographers)x.display();
        if(photographers.empty())cout<<"No photographers.\n";
    }
    void listK()const {
        for(auto&x:packages)x->display();
        if(packages.empty())cout<<"No packages.\n";
    }
    void listB()const {
        for(auto&x:bookings)x.display();
        if(bookings.empty())cout<<"No bookings.\n";
    }
    void customerMenu() {
        while(true) {
            cout<<"\nCUSTOMERS 1 Add 2 List 3 Search 4 Update 5 Delete 0 Back\n";
            int ch=integer("Choice: ");
            if(!ch)return;
            if(ch==1) {
                string n=input("Name: "),p=input("Phone: "),e=input("Email: ");
                if(n.empty()||p.empty()||phoneUsed(p)) {
                    cout<<"Invalid name/phone or duplicate phone.\n";
                    continue;
                }
                customers.emplace_back(nc++,n,p,e);
                saveAll();
            }
            else if(ch==2)listC();
            else if(ch==3) {
                auto x=fc(integer("ID: "));
                if(x)x->display();
                else cout<<"Not found.\n";
            }
            else if(ch==4) {
                int id=integer("ID: ");
                auto x=fc(id);
                if(!x) {
                    cout<<"Not found.\n";
                    continue;
                }
                string n=input("New name (blank=keep): "),p=input("New phone (blank=keep): "),e=input("New email (blank=keep): ");
                if(!p.empty()&&phoneUsed(p,id)) {
                    cout<<"Duplicate phone; no changes made.\n";
                    continue;
                }
                if(!n.empty())x->setName(n);
                if(!p.empty())x->setPhone(p);
                if(!e.empty())x->setEmail(e);
                saveAll();
            }
            else if(ch==5) {
                int id=integer("ID: ");
                bool active=false;
                for(auto&b:bookings)if(b.getCustomer()==id&&b.getStatus()!="Cancelled")active=true;
                auto it=find_if(customers.begin(),customers.end(),[&](Customer&x){return x.getId()==id;});
                if(it==customers.end())cout<<"Not found.\n";
                else if(active)cout<<"Active booking prevents deletion.\n";
                else {
                    customers.erase(it);
                    saveAll();
                    cout<<"Deleted.\n";
                }
            }
            else cout<<"Invalid choice.\n";
        }
    }
    void photographerMenu() {
        while(true) {
            cout<<"\nPHOTOGRAPHERS 1 Add 2 List 3 Search 4 Update 5 Delete 0 Back\n";
            int ch=integer("Choice: ");
            if(!ch)return;
            if(ch==1) {
                string n=input("Name: "),p=input("Phone: "),e=input("Email: "),s=input("Specialty: ");
                double r=number("Daily rate: ");
                if(n.empty()||p.empty()) {
                    cout<<"Name and phone required.\n";
                    continue;
                }
                photographers.emplace_back(np++,n,p,e,s,r);
                saveAll();
            }
            else if(ch==2)listP();
            else if(ch==3) {
                auto x=fp(integer("ID: "));
                if(x)x->display();
                else cout<<"Not found.\n";
            }
            else if(ch==4) {
                auto x=fp(integer("ID: "));
                if(!x) {
                    cout<<"Not found.\n";
                    continue;
                }
                string n=input("Name (blank=keep): "),p=input("Phone (blank=keep): "),e=input("Email (blank=keep): "),s=input("Specialty (blank=keep): "),r=input("Rate (blank=keep): ");
                double v;
                if(!r.empty()&&(!pd(r,v)||v<0)) {
                    cout<<"Invalid rate; no changes made.\n";
                    continue;
                }
                if(!n.empty())x->setName(n);
                if(!p.empty())x->setPhone(p);
                if(!e.empty())x->setEmail(e);
                if(!s.empty())x->setSpecialty(s);
                if(!r.empty())x->setRate(v);
                saveAll();
            }
            else if(ch==5) {
                int id=integer("ID: ");
                bool active=false;
                for(auto&b:bookings)if(b.getPhotographer()==id&&b.getStatus()!="Cancelled")active=true;
                auto it=find_if(photographers.begin(),photographers.end(),[&](Photographer&x){return x.getId()==id;});
                if(it==photographers.end())cout<<"Not found.\n";
                else if(active)cout<<"Active booking prevents deletion.\n";
                else {
                    photographers.erase(it);
                    saveAll();
                    cout<<"Deleted.\n";
                }
            }
            else cout<<"Invalid choice.\n";
        }
    }
    void packageMenu() {
        while(true) {
            cout<<"\nPACKAGES 1 Add 2 List 3 Search 4 Update 5 Delete 0 Back\n";
            int ch=integer("Choice: ");
            if(!ch)return;
            if(ch==1) {
                string n=input("Name: ");
                if(n.empty()) {
                    cout<<"Name required.\n";
                    continue;
                }
                double p=number("Base price: ");
                int h=integer("Duration hours: ");
                if(h<=0) {
                    cout<<"Hours must be positive.\n";
                    continue;
                }
                if(integer("Premium? 1 yes, 0 no: ")==1)packages.emplace_back(new PremiumPackage(nk++,n,p,h,number("Premium charge: ")));
                else packages.emplace_back(new Package(nk++,n,p,h));
                saveAll();
            }
            else if(ch==2)listK();
            else if(ch==3) {
                auto x=fk(integer("ID: "));
                if(x)x->display();
                else cout<<"Not found.\n";
            }
            else if(ch==4) {
                auto x=fk(integer("ID: "));
                if(!x) {
                    cout<<"Not found.\n";
                    continue;
                }
                string n=input("Name (blank=keep): "),ps=input("Price (blank=keep): "),hs=input("Hours (blank=keep): ");
                double p;
                int h;
                if(!ps.empty()&&(!pd(ps,p)||p<0)) {
                    cout<<"Invalid price.\n";
                    continue;
                }
                if(!hs.empty()&&(!pi(hs,h)||h<=0)) {
                    cout<<"Invalid hours.\n";
                    continue;
                }
                auto q=dynamic_cast<PremiumPackage*>(x);
                string es;
                double e;
                if(q)es=input("Premium charge (blank=keep): ");
                if(!es.empty()&&(!pd(es,e)||e<0)) {
                    cout<<"Invalid charge.\n";
                    continue;
                }
                if(!n.empty())x->setName(n);
                if(!ps.empty())x->setPrice(p);
                if(!hs.empty())x->setHours(h);
                if(q&&!es.empty())q->setExtra(e);
                saveAll();
            }
            else if(ch==5) {
                int id=integer("ID: ");
                bool active=false;
                for(auto&b:bookings)if(b.getPackage()==id&&b.getStatus()!="Cancelled")active=true;
                auto it=find_if(packages.begin(),packages.end(),[&](unique_ptr<Package>&x){return x->getId()==id;});
                if(it==packages.end())cout<<"Not found.\n";
                else if(active)cout<<"Active booking prevents deletion.\n";
                else {
                    packages.erase(it);
                    saveAll();
                    cout<<"Deleted.\n";
                }
            }
            else cout<<"Invalid choice.\n";
        }
    }
    void createBooking() {
        if(customers.empty()||photographers.empty()||packages.empty()) {
            cout<<"Add customer, photographer, and package first.\n";
            return;
        }
        listC();
        int c=integer("Customer ID: ");
        if(!fc(c)) {
            cout<<"Invalid customer.\n";
            return;
        }
        listP();
        int p=integer("Photographer ID: ");
        if(!fp(p)) {
            cout<<"Invalid photographer.\n";
            return;
        }
        listK();
        int k=integer("Package ID: ");
        auto pack=fk(k);
        if(!pack) {
            cout<<"Invalid package.\n";
            return;
        }
        string d=input("Date YYYY-MM-DD: ");
        if(!dateOK(d)) {
            cout<<"Invalid date.\n";
            return;
        }
        if(busy(p,d)) {
            cout<<"Photographer already booked on this date.\n";
            return;
        }
        string e=input("Event type: ");
        if(e.empty()) {
            cout<<"Event required.\n";
            return;
        }
        bookings.emplace_back(nb++,c,p,k,d,e,pack->total());
        saveAll();
        cout<<"Booking confirmed. ID "<<bookings.back().getId()<<", total Rs."<<pack->total()<<"\n";
    }
    void bookingMenu() {
        while(true) {
            cout<<"\nBOOKINGS 1 Create 2 List 3 Search 4 Update 5 Cancel 6 Permanent delete 0 Back\n";
            int ch=integer("Choice: ");
            if(!ch)return;
            if(ch==1)createBooking();
            else if(ch==2)listB();
            else if(ch==3) {
                auto b=fb(integer("Booking ID: "));
                if(b)b->display();
                else cout<<"Not found.\n";
            }
            else if(ch==4) {
                int id=integer("Booking ID: ");
                auto b=fb(id);
                if(!b||b->getStatus()=="Cancelled") {
                    cout<<"Booking not found or cancelled.\n";
                    continue;
                }
                string ds=input("New date (blank=keep): "),es=input("New event (blank=keep): "),ps=input("New photographer ID (blank=keep): "),ks=input("New package ID (blank=keep): ");
                string d=ds.empty()?b->getDate():ds;
                int p=b->getPhotographer(),k=b->getPackage();
                if(!ps.empty()&&!pi(ps,p)) {
                    cout<<"Bad photographer ID.\n";
                    continue;
                }
                if(!ks.empty()&&!pi(ks,k)) {
                    cout<<"Bad package ID.\n";
                    continue;
                }
                auto pack=fk(k);
                if(!fp(p)||!pack||!dateOK(d)||busy(p,d,id)) {
                    cout<<"Invalid selection/date or photographer unavailable.\n";
                    continue;
                }
                b->setDate(d);
                if(!es.empty())b->setEvent(es);
                b->setPhotographer(p);
                b->setPackage(k);
                b->setAmount(pack->total());
                saveAll();
                cout<<"Updated.\n";
            }
            else if(ch==5) {
                auto b=fb(integer("Booking ID: "));
                if(!b)cout<<"Not found.\n";
                else if(b->getStatus()=="Cancelled")cout<<"Already cancelled.\n";
                else {
                    b->setStatus("Cancelled");
                    saveAll();
                    cout<<"Cancelled.\n";
                }
            }
            else if(ch==6) {
                int id=integer("Booking ID to permanently delete: ");
                auto it=find_if(bookings.begin(),bookings.end(),[&](Booking&b){return b.getId()==id;});
                if(it==bookings.end())cout<<"Not found.\n";
                else {
                    bookings.erase(it);
                    saveAll();
                    cout<<"Permanently deleted.\n";
                }
            }
            else cout<<"Invalid choice.\n";
        }
    }
    public:
    StudioSystem() {
        load();
    }
    ~StudioSystem() {
        saveAll();
    }
    void run() {
        while(true) {
            cout<<"\n=== PHOTOGRAPHY STUDIO MANAGEMENT ===\n1 Customers\n2 Photographers\n3 Packages\n4 Bookings\n5 Summary report\n6 Save data\n0 Save and exit\n";
            int c=integer("Choice: ");
            if(c==1)customerMenu();
            else if(c==2)photographerMenu();
            else if(c==3)packageMenu();
            else if(c==4)bookingMenu();
            else if(c==5) {
                int active=0;
                double rev=0;
                for(auto&b:bookings)if(b.getStatus()!="Cancelled") {
                    active++;
                    rev+=b.getAmount();
                }
                cout<<"Customers: "<<customers.size()<<"\nPhotographers: "<<photographers.size()<<"\nPackages: "<<packages.size()<<"\nBookings: "<<bookings.size()<<"\nActive bookings: "<<active<<"\nBooking value: Rs."<<rev<<"\n";
            }
            else if(c==6) {
                saveAll();
                cout<<"Saved.\n";
            }
            else if(c==0) {
                saveAll();
                cout<<"Saved. Goodbye.\n";
                return;
            }
            else cout<<"Invalid choice.\n";
        }
    }
}
;
int main() {
    StudioSystem app;
    app.run();
    return 0;
}
