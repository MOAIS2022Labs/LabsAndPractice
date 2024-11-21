using Microsoft.VisualBasic.Devices;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7
{
    [Serializable]
    public class Exam
    {       
        public string Subject { get; set; }
        private byte _mark;
        public byte Mark
        {
            get
            {
                   return _mark;
            }
            set
            {
                if (value < 2 || value > 5)
                    throw new ArgumentOutOfRangeException("Оценка должна находиться в диапазоне от 2 до 5");
                _mark = value;
            }
        }
        public Exam()
        {
            Subject = string.Empty;
            _mark = 2;
        }
        public Exam(string subject, byte mark)
        {
            Subject = subject;
            Mark = mark;
        }
        public bool isBad()
        {
            return Mark == 2;
        }
        public override string ToString() 
        {
            return $"{Subject}: {_mark}";
        }
    }

    [Serializable]
    public class Student
    {
        public enum EEducationForm { Budget, Contract }
        public string FIO { get; set; }
        private byte _course;
        public byte Course
        {
            get { return _course; }
            set
            {
                if (value < 1 || value > 4)
                    throw new ArgumentOutOfRangeException("Несуществующий номер курса");
                _course = value;
            }
        }
        private byte _group;
        public byte Group
        {
            get { return _group; }
            set
            {
                if (value < 0 || value > 100)
                    throw new ArgumentOutOfRangeException("Несуществующий номер группы");
                _group = value;
            }
        }
        public Exam[] Exams { get; set; }
        public EEducationForm EducationForm { get; set; }
        static public readonly byte CountExams = 5;
        static public readonly byte CountSessions = 8;
        public Student() 
        { 
            FIO = string.Empty;
            _group = 1;
            _course = 1;
            Exams = new Exam[CountExams * CountSessions];
            for (var i = 0; i < Exams.Length; ++i)
                Exams[i] = new Exam();
            EducationForm = EEducationForm.Contract;
        }
        public Student(string fio, byte course, byte group, Exam[] exams, EEducationForm educationForm)
        {
            FIO = fio;
            _course = course;
            _group = group;
            Exams = exams;
            EducationForm = educationForm;
        }
        public Student(StreamReader sr)
        {
            FIO = sr.ReadLine();
            Course = byte.Parse(sr.ReadLine());
            Group = byte.Parse(sr.ReadLine());

            int examNum = CountExams * _course * 2;
            Exams = new Exam[examNum];

            for (var i = 0; i < examNum; ++i)
            {
                var lines = sr.ReadLine().Split(':');
                var subject = lines[0];
                var mark = byte.Parse(lines[1].Trim());
                Exams[i] = new Exam(subject, mark);
            }
            if (sr.ReadLine().ToLower() == "бюджет")
            {
                EducationForm = EEducationForm.Budget;
            }
            else
            {
                EducationForm = EEducationForm.Contract;
            }
        }
        
        public string ToListBox()
        {
            return $"{FIO}, {_course}-й курс, группа {_group}, {(EducationForm == EEducationForm.Budget ? "бюджет" : "договор")}";
        }

        public override string ToString()
        {
            string result =  $"{FIO}\n{_course}\n{_group}\n";
            int examNum = _course * CountExams * 2;
            for (var i = 0; i < examNum; ++i)
                result += Exams[i].ToString() + "\n";
            result += EducationForm == EEducationForm.Budget ? "Бюджет" : "Договор";
            return result;
        }
    }
}
