#ifndef NO_H
#define NO_H


class No
{
private:
    int info;
    No *prox;
public:
    No(int info);
    ~No()                 { };
    int getInfo()         { return info; };
    No* getProx()         { return prox; };
    void setInfo(int info) { No::info = info; };
    void setProx(No *prox)   { No::prox = prox; };
};

#endif
