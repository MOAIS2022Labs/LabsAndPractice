using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_2_Lab_CSharp_Ants.Models
{
    //личинка - наследует насекомое
    public class Larva : Insect
    {
        public Larva()
        {
            NEEDFUL_FOOD_SIZE = 1;
            MAX_WAITING_TIME = 1;
            State = true;
        }
        //метод создания муравья
        //создает новый экземпляр муравья(в зависимости от Random - солддата, полицейского или рабочего)
        //возвращает тип класса созданного муравья
        //реализует шаблон Фабрика
        public Type CreateAnt(List<SoldierAnt> soldierAnts, List<PoliceAnt> policeAnts, List<WorkerAnt> workerAnts)
        {
            int type = new Random().Next() % 3;
            Type result;
            switch (type)
            {
                case 0:
                    result = (Type)new SoldierAnt().GetType();
                    soldierAnts.Add(new SoldierAnt());
                    break;
                case 1:
                    result = (Type)new PoliceAnt().GetType();
                    policeAnts.Add(new PoliceAnt());
                    break;
                default:
                    result = (Type)new WorkerAnt().GetType();
                    workerAnts.Add(new WorkerAnt());
                    break;
            }
            State = false;
            return result;
        }
    }
}
