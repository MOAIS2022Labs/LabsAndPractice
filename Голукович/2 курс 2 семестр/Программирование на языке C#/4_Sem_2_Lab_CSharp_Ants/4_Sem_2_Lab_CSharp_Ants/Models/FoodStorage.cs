using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _4_Sem_2_Lab_CSharp_Ants.Models
{
    //хранилище еды муравейника
    public class FoodStorage
    {
        private Queue<int> foodStorage;
        private int maxStorageSize;
        //событие изменения количества еды в хранилище
        public event Action<int> ChangeFoodStorage = delegate { };
        //свойство Количество
        public int Count { get => foodStorage.Count; }
        //объект синхронизации
        private object lockObject;
        //конструктор
        public FoodStorage(int max_storage_size, object lockObject)
        {
            this.maxStorageSize = max_storage_size;
            foodStorage = new Queue<int>();
            this.lockObject = lockObject;
        }
        //добавление еды в хранилище
        public void Add(int value)
        {
            lock(lockObject)
            {
                if (foodStorage.Count < maxStorageSize)
                    foodStorage.Enqueue(value);
                //вызов события изменения количества еды в хранилище
                ChangeFoodStorage(value);
            }
        }
        //извлечение еды из хранилища
        public void Get(ref int value)
        {
            lock (lockObject)
            {
                if (foodStorage.Count > 0)
                    value = foodStorage.Dequeue();
                //вызов события изменения количества еды в хранилище
                ChangeFoodStorage(value * -1);
            }
        }
    }
}
