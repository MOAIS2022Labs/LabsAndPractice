using System;
using System.Collections.Generic;
using System.Dynamic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_2_Lab_CSharp_Ants.Models
{
    //королева(матка) - наследует насекомое
    public class Queen : Insect
    {
        public Queen()
        {
            NEEDFUL_FOOD_SIZE = 20;
            MAX_WAITING_TIME = 5;
            State = true;
        }
        //метод Работа - создает новые личинки если их нет в муравейнике
        public Type Work(List<Larva> larvae, List<SoldierAnt> soldierAnts, List<PoliceAnt> policeAnts, List<WorkerAnt> workerAnts, object lockObject, ref int count)
        {
            Type type = (Type)new object().GetType();
            lock (lockObject)
            {
                //если мертва - исключение о смерти
                if (!State)
                    throw new DeadException();
                //если количество личинок пусто - создание новых
                if (larvae.Count == 0)
                {
                    count = new Random().Next() % 3 + 1;
                    for (int i = 0; i < count; ++i)
                        larvae.Add(new Larva());
                }
                //работа фабрики личинки по созданию новых муравьев
                type = larvae[0].CreateAnt(soldierAnts, policeAnts, workerAnts);
            }
            //возвращает тип класса муравья, созданного фабрикой-личинкой
            return type;
        }
    }
}
