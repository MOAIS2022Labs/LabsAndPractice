using System.Collections.Generic;
using System.Linq;

namespace _4_Sem_2_Lab_CSharp_Ants.Models
{
    //муравей солдат -  - наследует насекомое
    public class SoldierAnt : Insect
    {
        public SoldierAnt()
        {
            NEEDFUL_FOOD_SIZE = 15;
            MAX_WAITING_TIME = 4;
            State = true; 
        }
        //метод работа - убивает одного вредителя в муравейнике
        public void Work(List<Pest> pests, object lockObject)
        {
            lock (lockObject)
            {
                //если мертв - исключение о смерти
                if (!State)
                    throw new DeadException();
                //убивает первого в списке вредителей
                if (pests.Count > 0)
                    pests.First().Kill();
            }
        }
    }
}
