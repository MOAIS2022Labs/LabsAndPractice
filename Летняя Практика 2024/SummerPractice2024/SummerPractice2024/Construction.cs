using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.ListView;

namespace SummerPractice2024
{
    public class Construction : IEnumerable<Detail>
    {
        private List<Detail> _details;
        public int Toughness { get; private set; }
        public int Speed { get; private set; }
        public int Damage { get; private set; }
        public int Price { get; private set; }
        public Construction()
        {
            _details = new();
            Toughness = 0;
            Speed = 0;
            Damage = 0;
            Price = 0;
        }
        public IEnumerator<Detail> GetEnumerator()
        {
            return _details.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void Add(Detail detail)
        {
            _details.Add(detail);
            Toughness += detail.Toughness;
            Speed += detail.Speed;
            Damage += detail.Damage;
            Price += detail.Price;
        }

        public void PopBack()
        {
            var detail = _details[_details.Count - 1];
            _details.RemoveAt(_details.Count - 1);
            Toughness -= detail.Toughness;
            Speed -= detail.Speed;
            Damage -= detail.Damage;
            Price -= detail.Price;
        }

        public bool Empty()
        {
            return _details.Count == 0;
        }

        public bool Destroy()
        {
            if (_details.Count == 0)
                return false;
            _details.Clear();
            Toughness = 0;
            Speed = 0;
            Damage = 0;
            Price = 0;
            return true;
        }

        public bool IntersectWith(Detail detail)
        {
            return _details.Any(d => d.IntersectWith(detail));
        }
    }
}
