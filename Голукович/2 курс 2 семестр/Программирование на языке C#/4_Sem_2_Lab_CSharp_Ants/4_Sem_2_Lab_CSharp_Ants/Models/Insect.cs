using System.Threading;

namespace _4_Sem_2_Lab_CSharp_Ants.Models
{
    //насекомое - абстрактный класс, который наследуется всеми насекомыми муравейника
    public abstract class Insect
    {
        //состояние (жив/мертв)
        public bool State { get; protected set; }
        //необходимое количество еды для кормежки
        protected int NEEDFUL_FOOD_SIZE;
        //максимальное количество времени ожидания кормежки
        protected int MAX_WAITING_TIME;
        //мгновенная смерть
        public void Kill() => State = false;
        //поедание пищи
        public int Eat(FoodStorage foodStorage)
        {
            if (!State)
                //исключение, отлавливаемое в коде, который вызвал метод
                throw new DeadException();
            int foodSize = 0;
            int waiting = 0;
            //пока не наестся или не истечет время ожидания кормежки
            while (foodSize < NEEDFUL_FOOD_SIZE && waiting < MAX_WAITING_TIME)
            {
                int addedFoodSize = 0;
                //попробовать взять еду из хранилища
                foodStorage.Get(ref addedFoodSize);
                //если не взяли - ждем
                if (addedFoodSize == 0)
                    waiting++;
                Thread.Sleep(1000);
                foodSize += addedFoodSize;
            }
            //если насекомое не наелось - оно умирает
            if (waiting == MAX_WAITING_TIME && foodSize < NEEDFUL_FOOD_SIZE)
            {
                State = false;
                throw new DeadException();
            }
            return foodSize;
        }
    }
}
