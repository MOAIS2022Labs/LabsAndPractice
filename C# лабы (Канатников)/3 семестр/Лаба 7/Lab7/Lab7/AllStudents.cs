using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;
using System.Xml.Serialization;

namespace Lab7
{

   
    public class AllStudents
    {
        public List<Student> Students = new List<Student>();
        public AllStudents() 
        {
            Students = new List<Student>();
        }

        public void OpenTxtFile(string fileName)
        {
            var sr = new StreamReader(fileName);
            try
            {
                while (!sr.EndOfStream)
                {
                    var student = new Student(sr);
                    Students.Add(student);
                }
            }
            catch (FormatException ex)
            {
                Students.Clear();
                MessageBox.Show("Числа в файле должны быть положительными цифрами", "Некорректный файл!", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (ArgumentOutOfRangeException ex) 
            {
                Students.Clear();
                MessageBox.Show(ex.Message, "Некорректный файл!", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (IndexOutOfRangeException ex)
            {
                Students.Clear();
                MessageBox.Show("Номер курса не соответствует количеству сессий", "Некорректный файл!", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex) 
            {
                Students.Clear();
                MessageBox.Show(ex.Message, "Некорректный файл!", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            { 
                sr.Close(); 
            }

        }
        public void SaveTxtFile(string fileName)
        {
            using (var  sw = new StreamWriter(fileName))
            {
                foreach (var student in Students)
                    sw.WriteLine(student);
            }
        }

        public void OpenBinFile(string fileName)
        {
            var binFormatter = new BinaryFormatter();
            var file = new FileStream(fileName, FileMode.OpenOrCreate);
            try
            {
                Students = binFormatter.Deserialize(file) as List<Student>;
            }
            catch (Exception ex)
            {
                Students.Clear();
                MessageBox.Show(ex.Message, "Некорректный файл!", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally 
            { 
                file.Close(); 
            }
        }
        public void SaveBinFile(string fileName)
        {
            var binFormatter = new BinaryFormatter();
            using (var file = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                binFormatter.Serialize(file, Students);
            }
        }

        public void OpenXmlFile(string fileName)
        {
            var xmlFormatter = new XmlSerializer(typeof(List<Student>));
            var file = new FileStream(fileName, FileMode.OpenOrCreate);
            try
            {
                Students = xmlFormatter.Deserialize(file) as List<Student>;
            }       
            catch (Exception ex)
            {
                Students.Clear();
                MessageBox.Show(ex.Message, "Некорректный файл!", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            finally
            {
                file.Close();
            }
        }

        public void SaveXmlFile(string fileName)
        {
            var xmlFormatter = new XmlSerializer(typeof(List<Student>));    
            using (var file = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                xmlFormatter.Serialize(file, Students);
            }
        }
        // найти предметы, по которым нет неуспевающих
        public List<string> ListOfSubjectsWithoutBadMarks()
        {
            var result = new List<string>();
            var subjectsDictionary = new Dictionary<string, bool>(); // ключ - название предмета,
                                                                     // значение - по предмету не было двоек
            foreach(var student in Students)
            {
                foreach (var exam in student.Exams)
                { 
                    if (!subjectsDictionary.ContainsKey(exam.Subject))
                        subjectsDictionary.Add(exam.Subject, true);
                    if (exam.isBad())
                        subjectsDictionary[exam.Subject] = false;
                }
            }
            foreach (var subject in subjectsDictionary)
                if (subject.Value)
                    result.Add(subject.Key);
            return result;
        }         
        
        // найти предметы, которые читают на нескольких курсах
        public List<string> Task()
        {
            var result = new List<String>();

            var subjects = new Dictionary<string, List<int>>(); // ключ - название предмета
                                                                // значение - курсы, на которых читается
            foreach(var student in Students)
            {
                for (var i = 0; i < student.Exams.Count(); i++)
                {
                    if (!subjects.ContainsKey(student.Exams[i].Subject))
                        subjects.Add(student.Exams[i].Subject, new List<int>());
                    int course = i / 10 + 1; // с какого курса этот предмет
                    if (!subjects[student.Exams[i].Subject].Contains(course))
                        subjects[student.Exams[i].Subject].Add(course);
                }
            }
            foreach(var subject in subjects)
                if (subject.Value.Count > 1)
                    result.Add(subject.Key);
            return result;
        }
    }
}
