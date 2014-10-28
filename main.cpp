#include <QFile>
#include <QList>
#include <QString>
#include <QStringList>
#include <QMap>
#include <iostream>
typedef QList< QList<int>* > RankList ;


RankList GetFromFile(QFile &file)
{
    RankList rankList;
    QString line;
    QStringList slist;
    QList<int> *one;
    file.open(QIODevice::ReadOnly);
    for(int i=0;!file.atEnd();i++)
    {
        one = new QList<int>;
        line=file.readLine();
        slist=line.split(" ");
        for(int j=1;j<slist.size();j++)
        {
            one->append(slist.at(j).mid(1).toInt());
        }
        rankList.append(one);
    }
    file.close();
    return rankList;
}

void GetMatch(RankList &boys,RankList &girls,QFile &file)
{
    QMap<int,int> matchResult,matchResultIndexByBoy;
    QList<int> freeBoys;
    for(int i=0;i<boys.size();i++)
    {
        freeBoys.append(i);
    }
    int boy,girl;
    while(!freeBoys.isEmpty())
    {
        boy=freeBoys.first();
        girl=boys.at(boy)->first();
        if( matchResult.contains(girl) )
        {
            for(int j=0;j<girls.at(girl)->size();j++)
            {
                if(girls.at(girl)->at(j)==boy)
                {
                    freeBoys.removeFirst();
                    freeBoys.insert(0,matchResult[girl]);
                    matchResult[girl]=boy;
                    boys.at(boy)->removeFirst();
                    break;
                }
                else if(girls.at(girl)->at(j)==matchResult[girl])
                {
                    boys.at(boy)->removeFirst();
                    break;
                }
            }
        }
        else
        {
            matchResult.insert(girl,boy);
            boys.at(boy)->removeFirst();
            freeBoys.removeFirst();
        }
    }
    file.open(QIODevice::WriteOnly);
    QMap<int,int>::iterator it;
    matchResultIndexByBoy.clear();
    for(it=matchResult.begin();it!=matchResult.end();it++)
    {
//        file.write("(B"+QByteArray().setNum(it.value())+",G"+QByteArray().setNum(it.key())+") ");
        matchResultIndexByBoy.insert(it.value(),it.key());
    }
//    file.write("\n");
    for(it=matchResultIndexByBoy.begin();it!=matchResultIndexByBoy.end();it++)
    {
        file.write("(B"+QByteArray().setNum(it.key())+",G"+QByteArray().setNum(it.value())+") ");
    }
    file.close();
}

int main(int argc, char *argv[])
{
    RankList boys,girls;
    QFile file;
    file.setFileName("boys_rankings.txt");
    boys=GetFromFile(file);
    file.setFileName("girls_rankings.txt");
    girls=GetFromFile(file);
    file.setFileName("match_result.txt");
    GetMatch(boys,girls,file);
    std::cout<<"complete!";
}
