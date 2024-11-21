using System;
using System.Collections.Generic;
using System.Data;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab6
{
    public class Matrix
    {
        public int Row { get; set; }
        public int Col { get; set; }
        private int[,] matrix;

        public Matrix(int n)
        {
            Row = n;
            Col = n;
            matrix = new int[Row, Col];
        }
        public bool GridToMatrix(DataGridView Grid)
        {
            DataGridViewCell Cell;
            for (var i = 0; i < Row; i++)
            {
                for (var j = 0; j < Col; j++)
                {
                    Cell = Grid.Rows[i].Cells[j];
                    string s = Cell.Value.ToString();
                    if (s == "")
                        matrix[i, j] = 0;
                    else
                        if (!int.TryParse(s, out matrix[i, j]))                          
                            return false;
                }
            }
            return true;
        }
        public void MatrixToGrid(DataGridView Grid)
        {
            int i;
            DataTable matr = new DataTable("Matrix");
            DataColumn[] columns = new DataColumn[Col];
            for (i = 0; i < Col; ++i)
            {
                columns[i] = new DataColumn(i.ToString());
                matr.Columns.Add(columns[i]);
            }
            for (i = 0; i < Row; ++i)
            {
                DataRow newRow = matr.NewRow();
                matr.Rows.Add(newRow);
            }
            Grid.DataSource = matr;
            for (i = 0; i < Col; ++i)
                Grid.Columns[i].Width = 50;
            DataGridViewCell Cell;
            for (i = 0; i < Row; ++i)
            {
                for (int j = 0; j < Col; j++)
                {
                    Cell = Grid.Rows[i].Cells[j];
                    Cell.Value = matrix[i, j];
                }
            }
        }
        public void Task()
        {
            ++Row;
            int[,] new_matrix = new int[Row, Col];
            for (var i = 0; i < Row - 1; ++i)
            {
                int max = matrix[i, 0];
                new_matrix[i, 0] = max;
                for (var j = 1; j < Col; ++j)
                {
                    new_matrix[i, j] = matrix[i, j];
                    if (matrix[i, j] > max)
                        max = matrix[i, j];
                }
                new_matrix[Row - 1, i] = max;
            }
            matrix = new_matrix;
        }
    }
}
