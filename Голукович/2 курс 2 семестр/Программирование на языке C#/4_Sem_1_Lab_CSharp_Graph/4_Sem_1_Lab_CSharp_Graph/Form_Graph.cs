using _4_Sem_1_Lab_CSharp;
using System;
using Microsoft.Msagl;
using Microsoft.Msagl.Drawing;
using System.Windows.Forms;

namespace _4_Sem_1_Lab_CSharp_Graph
{
    public partial class Form_Graph : Form
    {
        public Form_Graph()
        {
            InitializeComponent();
        }

        private IGraph<int, int> intGraph = new ArrayGraph<int, int>();
        private IGraph<string, int> stringGraph = new ArrayGraph<string, int>();
        private IGraph<int, int> currentIntGraph = new ArrayGraph<int, int>();
        private IGraph<string, int> currentStringGraph = new ArrayGraph<string, int>();
        int isUnmutable = 0;
        int graphNodeType = 0;

        private void toolStripMenuItem_IntIntArrayGraph_Click(object sender, EventArgs e)
        {
            intGraph = new ArrayGraph<int, int>(); ;
            currentIntGraph = new ArrayGraph<int, int>();
            stringGraph = new ArrayGraph<string, int>();
            currentStringGraph = new ArrayGraph<string, int>();
            graphNodeType = 1;
            isUnmutable = -1;
            MessageBox.Show("Граф на массиве int был создан!", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void toolStripMenuItem_StringIntArrayGraph_Click(object sender, EventArgs e)
        {
            intGraph = new ArrayGraph<int, int>();
            currentIntGraph = new ArrayGraph<int, int>();
            stringGraph = new ArrayGraph<string, int>();
            currentStringGraph = new ArrayGraph<string, int>();
            graphNodeType = -1;
            isUnmutable = -1;
            MessageBox.Show("Граф на массиве string был создан!", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void toolStripMenuItem_IntIntLinkedGraph_Click(object sender, EventArgs e)
        {
            intGraph = new LinkedGraph<int, int>();
            currentIntGraph = new LinkedGraph<int, int>();
            stringGraph = new LinkedGraph<string, int>();
            currentStringGraph = new LinkedGraph<string, int>();
            graphNodeType = 1;
            isUnmutable = -1;
            MessageBox.Show("Граф на листе int был создан!", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void toolStripMenuItem_StringIntLinkedGraph_Click(object sender, EventArgs e)
        {
            intGraph = new LinkedGraph<int, int>();
            currentIntGraph = new LinkedGraph<int, int>();
            stringGraph = new LinkedGraph<string, int>();
            currentStringGraph = new LinkedGraph<string, int>();
            graphNodeType = -1;
            isUnmutable = -1;
            MessageBox.Show("Граф на листе string был создан!", "Успех", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void toolStripMenuItem_MakeUnmutableMutable_Click(object sender, EventArgs e)
        {
            switch (isUnmutable)
            {
                case -1:
                    {
                        switch (graphNodeType)
                        {
                            case 1:
                                intGraph = currentIntGraph;
                                currentIntGraph = new UnmutableGraph<int, int>(currentIntGraph);
                                break;
                            case -1:
                                stringGraph = currentStringGraph;
                                currentStringGraph = new UnmutableGraph<string, int>(currentStringGraph);
                                break;
                            default:
                                MessageBox.Show("Граф не может быть изменяемым в данный момент!", "Ошибка!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                return;
                        }
                        isUnmutable = 1;
                        MessageBox.Show("Теперь граф нельзя изменять!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    break;
                case 1:
                    {
                        switch (graphNodeType)
                        {
                            case 1:
                                currentIntGraph = intGraph;
                                break;
                            case -1:
                                currentStringGraph = stringGraph;
                                break;
                            default:
                                MessageBox.Show("Граф не может быть неизменяемым в данный момент!", "Ошибка!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                return;
                        }
                        isUnmutable = -1;
                        MessageBox.Show("Теперь граф можно изменять!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                    break;
                case 0:
                    MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    break;
            }
        }

        private void toolStripMenuItem_AddNode_Click(object sender, EventArgs e)
        {
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            Form_PickValue pickValue = new Form_PickValue("Node adding", "Введите значение вершины для добавления");
            pickValue.ShowDialog();
            if (pickValue.value != null && pickValue.value.Length > 0)
            {
                try
                {
                    if (graphNodeType == 1)
                    {
                        int value = 0;
                        if (int.TryParse(pickValue.value, out value))
                        {
                            currentIntGraph.AddNode(value);
                            MessageBox.Show("Вершина со значением " + pickValue.value + " была успешно добавлена!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }
                        else
                            MessageBox.Show("Неверный тип элемента!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                    else
                    {
                        currentStringGraph.AddNode(pickValue.value);
                        MessageBox.Show("Вершина со значением " + pickValue.value + " была успешно добавлена!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
                catch (DisabledAddGraphException exception)
                {
                    MessageBox.Show(exception.Message, "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                catch (DisabledChangeGraphException exception)
                {
                    MessageBox.Show(exception.Message + " Граф является неизменяемым!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            else
                MessageBox.Show("Пустое значение!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void toolStripMenuItem_RemoveNode_Click(object sender, EventArgs e)
        {
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            Form_PickValue pickValue = new Form_PickValue("Node removing", "Введите значение вершины для удаления");
            pickValue.ShowDialog();
            if (pickValue.value != null && pickValue.value.Length > 0)
            {
                try
                {
                    if (graphNodeType == 1)
                    {
                        int value = 0;
                        if (int.TryParse(pickValue.value, out value))
                        {
                            currentIntGraph.RemoveNode(value);
                            MessageBox.Show("Вершина со значением " + pickValue.value + " была успешно удалена!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }
                        else
                            MessageBox.Show("Неверный тип элемента!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                    else
                    {
                        currentStringGraph.RemoveNode(pickValue.value);
                        MessageBox.Show("Вершина со значением " + pickValue.value + " была успешно удалена!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
                catch (DisabledRemoveGraphException exception)
                {
                    MessageBox.Show(exception.Message, "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                catch (DisabledFindGraphException exception)
                {
                    MessageBox.Show(exception.Message, "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                catch (DisabledChangeGraphException exception)
                {
                    MessageBox.Show(exception.Message + " Граф является неизменяемым!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            else
                MessageBox.Show("Пустое значение!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void toolStripMenuItem_ContainsNode_Click(object sender, EventArgs e)
        {
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            Form_PickValue pickValue = new Form_PickValue("Node finding", "Введите значение вершины для поиска");
            pickValue.ShowDialog();
            if (pickValue.value != null && pickValue.value.Length > 0)
            {
                try
                {
                    if (graphNodeType == 1)
                    {
                        int value = 0;
                        if (int.TryParse(pickValue.value, out value))
                        {
                            Node<int> node = currentIntGraph.FindNode(value);
                            if (node != null)
                                MessageBox.Show("Вершина со значением " + pickValue.value + " существует в графе. Ее номер " + node.Number + " .", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            else
                                MessageBox.Show("Вершины со значением " + pickValue.value + " не существует в графе.", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }
                        else
                            MessageBox.Show("Неверный тип элемента!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                    else
                    {
                        currentStringGraph.RemoveNode(pickValue.value);
                        MessageBox.Show("Вершина со значением " + pickValue.value + " была успешно удалена!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    }
                }
                catch (DisabledFindGraphException exception)
                {
                    MessageBox.Show(exception.Message, "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                catch (DisabledChangeGraphException exception)
                {
                    MessageBox.Show(exception.Message + " Граф является неизменяемым!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            else
                MessageBox.Show("Пустое значение!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void toolStripMenuItem_AddEdge_Click(object sender, EventArgs e)
        {
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            Form_PickValue pickValue = new Form_PickValue("Edge adding", "Введите вес грани для добавления");
            pickValue.ShowDialog();
            if (pickValue.value != null && pickValue.value.Length > 0)
            {
                int weight;
                if (int.TryParse(pickValue.value, out weight))
                {
                    Form_PickValue pickValueNodeFrom = new Form_PickValue("Node picking", "Введите значение вершины, откуда будет добавлена грань");
                    Form_PickValue pickValueNodeTo = new Form_PickValue("Node picking", "Введите значение вершины, куда будет добавлена грань");
                    pickValueNodeFrom.ShowDialog();
                    pickValueNodeTo.ShowDialog();
                    if (pickValueNodeFrom.value != null && pickValueNodeFrom.value.Length > 0 && pickValueNodeTo.value != null && pickValueNodeTo.value.Length > 0)
                    {
                        try
                        {
                            if (graphNodeType == 1)
                            {
                                int valueFrom, valueTo;
                                if (int.TryParse(pickValueNodeFrom.value, out valueFrom) && int.TryParse(pickValueNodeTo.value, out valueTo))
                                {
                                    currentIntGraph.AddEdge(valueFrom, valueTo, weight);
                                    MessageBox.Show("Новое ребро было добавлено!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                                }
                                else
                                    MessageBox.Show("Неверный тип элемента!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            }
                            else
                                currentStringGraph.AddEdge(pickValueNodeFrom.value, pickValueNodeTo.value, weight);
                        }
                        catch (DisabledAddGraphException exception)
                        {
                            MessageBox.Show(exception.Message, "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                        catch (DisabledFindGraphException exception)
                        {
                            MessageBox.Show(exception.Message, "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                        catch (DisabledChangeGraphException exception)
                        {
                            MessageBox.Show(exception.Message + " Граф является неизменяемым!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                    }
                    else
                        MessageBox.Show("Пустое значение!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                else
                    MessageBox.Show("Неверный тип элемента!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
                MessageBox.Show("Пустое значение!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void toolStripMenuItem_FindDescendants_Click(object sender, EventArgs e)
        {
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            Form_PickValue pickValue = new Form_PickValue("Node descendants finding", "Введите значение вершины, потомков которой хотите найти");
            pickValue.ShowDialog();
            if (pickValue.value != null && pickValue.value.Length > 0)
            {
                try
                {
                    System.Windows.Forms.Form showGraphForm = new System.Windows.Forms.Form();
                    Microsoft.Msagl.Drawing.Graph showGraph = new("Graph");
                    if (graphNodeType == 1)
                    {
                        int valueNodeFrom;
                        if (int.TryParse(pickValue.value, out valueNodeFrom))
                        {
                            MyLinkedList<Node<int>> nodes = currentIntGraph.GetNodesList(valueNodeFrom);
                            nodes.Add(currentIntGraph.FindNode(valueNodeFrom));
                            foreach (Node<int> node in nodes)
                            {
                                MyLinkedList<Edge<int, int>> edges = GraphUtils<int, int>.GetEdgesList(currentIntGraph, node.Data);
                                if (edges.Count > 0)
                                {
                                    foreach (var edge in edges)
                                        showGraph.AddEdge(edge.From.ToString(), edge.To.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Green;
                                    showGraph.FindNode(node.Data.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Blue;
                                }
                                else
                                    showGraph.AddNode(node.Data.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Blue;
                            }
                        }
                        else
                        {
                            MessageBox.Show("Пустое значение!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            return;
                        }
                    }
                    else
                    {
                        MyLinkedList<Node<string>> nodes = currentStringGraph.GetNodesList(pickValue.value);
                        nodes.Add(currentStringGraph.FindNode(pickValue.value));
                        foreach (Node<string> node in nodes)
                        {
                            MyLinkedList<Edge<string, int>> edges = GraphUtils<string, int>.GetEdgesList(currentStringGraph, node.Data);
                            foreach (var edge in edges)
                                showGraph.AddEdge(edge.From.ToString(), edge.To.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Green;
                            showGraph.FindNode(node.Data).Attr.Color = Microsoft.Msagl.Drawing.Color.Blue;
                        }
                    }
                    Microsoft.Msagl.GraphViewerGdi.GViewer viewer = new();
                    viewer.Graph = showGraph;
                    showGraphForm.SuspendLayout();
                    viewer.Dock = System.Windows.Forms.DockStyle.Fill;
                    showGraphForm.Controls.Add(viewer);
                    showGraphForm.ResumeLayout();
                    showGraphForm.ShowDialog();
                }
                catch (DisabledFindGraphException exception)
                {
                    MessageBox.Show(exception.Message, "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
            else
                MessageBox.Show("Пустое значение!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void toolStripMenuItem_ShowGraph_Click(object sender, EventArgs e)
        {
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (graphNodeType == 1 && currentIntGraph.Count == 0 || graphNodeType == -1 && currentStringGraph.Count == 0)
                MessageBox.Show("Граф пуст!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
            {
                System.Windows.Forms.Form showGraphForm = new System.Windows.Forms.Form();
                Microsoft.Msagl.Drawing.Graph showGraph = new("Graph");
                if (graphNodeType == 1)
                {
                    foreach (var node in currentIntGraph)
                        showGraph.AddNode(node.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Blue;
                    foreach (var edge in currentIntGraph.Edges)
                        showGraph.AddEdge(edge.From.ToString(), edge.To.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Green;
                }
                else
                {
                    foreach (var node in currentStringGraph)
                        showGraph.AddNode(node.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Blue;
                    foreach (var edge in currentStringGraph.Edges)
                        showGraph.AddEdge(edge.From.ToString(), edge.To.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Green;
                }
                Microsoft.Msagl.GraphViewerGdi.GViewer viewer = new();
                viewer.Graph = showGraph;
                showGraphForm.SuspendLayout();
                viewer.Dock = System.Windows.Forms.DockStyle.Fill;
                showGraphForm.Controls.Add(viewer);
                showGraphForm.ResumeLayout();
                showGraphForm.ShowDialog();
            }
        }

        private void toolStripMenuItem_ClearGraph_Click(object sender, EventArgs e)
        {
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (graphNodeType == 1 && currentIntGraph.Count == 0 || graphNodeType == -1 && currentStringGraph.Count == 0)
                MessageBox.Show("Граф пуст!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
                try
                {
                    currentIntGraph.Clear();
                    currentStringGraph.Clear();
                    intGraph.Clear();
                    stringGraph.Clear();
                    MessageBox.Show("Граф очищен!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (DisabledChangeGraphException exception)
                {
                    MessageBox.Show(exception.Message + " Граф является неизменяемым!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
        }

        private void toolStripMenuItem_GraphUtils_ForEach_Click(object sender, EventArgs e)
        {
            void intDecrement(Node<int> node)
            {
                node.Data++;
            }
            void stringToUpper(Node<string> node)
            {
                node.Data = node.Data.ToUpper();
            }
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (graphNodeType == 1 && currentIntGraph.Count == 0 || graphNodeType == -1 && currentStringGraph.Count == 0)
                MessageBox.Show("Граф пуст!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
            {
                if (isUnmutable == 1)
                    MessageBox.Show("Граф неможет быть изменен!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                else
                {
                    if (graphNodeType == 1)
                        GraphUtils<int, int>.ForEach(currentIntGraph, intDecrement);
                    else
                        GraphUtils<string, int>.ForEach(currentStringGraph, stringToUpper);
                    MessageBox.Show("Граф был изменен!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
        }

        private void toolStripMenuItem_GraphUtils_Exists_Click(object sender, EventArgs e)
        {
            bool intIf(Node<int> node)  { return node.Data >= 0 && node.Data <= 10; }
            bool stringIf(Node<string> node) { return node.Data.CompareTo("a") == 1 && node.Data.CompareTo("A") == -1; }
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (graphNodeType == 1 && currentIntGraph.Count == 0 || graphNodeType == -1 && currentStringGraph.Count == 0)
                MessageBox.Show("Граф пуст!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
            {
                if (graphNodeType == 1)
                {
                    if (GraphUtils<int, int>.Exists(currentIntGraph, intIf))
                        MessageBox.Show("В графе существуют вершины со значениями от 0 до 10!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    else
                        MessageBox.Show("В графе не существуют вершины со значениями от 0 до 10!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                else
                {
                    if (GraphUtils<string, int>.Exists(currentStringGraph, stringIf))
                        MessageBox.Show("В графе не существуют вершины со значениями от a до A!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    else
                        MessageBox.Show("В графе не существуют вершины со значениями от a до A!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }

        private void toolStripMenuItem_GraphUtils_FindAll_Click(object sender, EventArgs e)
        {
            bool intIf(Node<int> node) { return node.Data < 0 || node.Data > 10; }
            bool stringIf(Node<string> node) { return node.Data.CompareTo("a") == 1 && node.Data.CompareTo("A") == -1; }
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (graphNodeType == 1 && currentIntGraph.Count == 0 || graphNodeType == -1 && currentStringGraph.Count == 0)
                MessageBox.Show("Граф пуст!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
            {
                IGraph<int, int> showIntGraph;
                IGraph<string, int> showStringGraph;
                bool flag = false;
                System.Windows.Forms.Form showGraphForm = new System.Windows.Forms.Form();
                Microsoft.Msagl.Drawing.Graph showGraph = new("Graph");
                if (graphNodeType == 1)
                {
                    showIntGraph = GraphUtils<int, int>.FindAll(currentIntGraph, intIf, GraphUtils<int, int>.ArrayGraphConstructor);
                    if (showIntGraph.Empty)
                    {
                        MessageBox.Show("В графе не существуют вершины со значениями вне диапазона от 0 до 10!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                    else
                    {
                        foreach (var node in showIntGraph)
                            showGraph.AddNode(node.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Blue;
                        foreach (var edge in showIntGraph.Edges)
                            showGraph.AddEdge(edge.From.ToString(), edge.To.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Green;
                    }
                }
                else
                {
                    showStringGraph = GraphUtils<string, int>.FindAll(currentStringGraph, stringIf, GraphUtils<string, int>.LinkedGraphConstructor);
                    if (showStringGraph.Empty)
                    {
                        MessageBox.Show("В графе не существуют вершины со значениями от a до A!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        return;
                    }
                    else
                    {
                        foreach (var node in showStringGraph)
                            showGraph.AddNode(node.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Blue;
                        foreach (var edge in showStringGraph.Edges)
                            showGraph.AddEdge(edge.From.ToString(), edge.To.ToString()).Attr.Color = Microsoft.Msagl.Drawing.Color.Green;
                    }
                }
                Microsoft.Msagl.GraphViewerGdi.GViewer viewer = new();
                viewer.Graph = showGraph;
                showGraphForm.SuspendLayout();
                viewer.Dock = System.Windows.Forms.DockStyle.Fill;
                showGraphForm.Controls.Add(viewer);
                showGraphForm.ResumeLayout();
                showGraphForm.ShowDialog();
            }
        }

        private void toolStripMenuItem_GraphUtils_CheckForAll_Click(object sender, EventArgs e)
        {
            bool intIf(Node<int> node) { return node.Data >= 0 && node.Data <= 10; }
            bool stringIf(Node<string> node) { return node.Data.CompareTo("a") == 1 && node.Data.CompareTo("A") == -1; }
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (graphNodeType == 1 && currentIntGraph.Count == 0 || graphNodeType == -1 && currentStringGraph.Count == 0)
                MessageBox.Show("Граф пуст!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
            {
                if (graphNodeType == 1)
                {
                    if (GraphUtils<int, int>.CheckForAll(currentIntGraph, intIf))
                        MessageBox.Show("Все вершины в графе со значениями от 0 до 10!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    else
                        MessageBox.Show("Не все вершины в графе со значениями от 0 до 10!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                else
                {
                    if (GraphUtils<string, int>.CheckForAll(currentStringGraph, stringIf))
                        MessageBox.Show("Все вершины в графе со значениями от a до A!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    else
                        MessageBox.Show("Не все вершины в графе со значениями от a до A!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }

        private void toolStripMenuItem_GraphUtils_Width_Click(object sender, EventArgs e)
        {
            bool intIf(Node<int> node) { return node.Data >= 0 && node.Data <= 10; }
            bool stringIf(Node<string> node) { return node.Data.CompareTo("a") == 1 && node.Data.CompareTo("A") == -1; }
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (graphNodeType == 1 && currentIntGraph.Count == 0 || graphNodeType == -1 && currentStringGraph.Count == 0)
                MessageBox.Show("Граф пуст!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
            {
                Form_PickValue pickValue = new Form_PickValue("Node descendants finding", "Введите значение вершины, потомков которой хотите найти");
                pickValue.ShowDialog();
                if (pickValue.value != null && pickValue.value.Length > 0)
                {
                    try
                    {
                        if (graphNodeType == 1)
                        {
                            int value;
                            if (int.TryParse(pickValue.value, out value))
                            {
                                if (GraphUtils<int, int>.FindWidth(currentIntGraph, value, intIf))
                                    MessageBox.Show("Вершина " + value.ToString() + "  и все ее потомки в графе со значениями в диапазоне от 0 до 10!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                                else
                                    MessageBox.Show("Вершина " + value.ToString() + " или ее потомки в графе со значениями вне диапазона от 0 до 10!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            }
                            else
                                MessageBox.Show("Неверный тип элемента!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                        else
                        {
                            if (GraphUtils<string, int>.FindWidth(currentStringGraph, pickValue.value, stringIf))
                                MessageBox.Show("Вершина " + pickValue.value + "  и все ее потомки в графе со значениями в диапазоне от a до A!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            else
                                MessageBox.Show("Вершина " + pickValue.value + " или ее потомки в графе со значениями вне диапазона от a до A!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                    }
                    catch (DisabledFindGraphException exception)
                    {
                        MessageBox.Show(exception.Message, "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                }
                else
                    MessageBox.Show("Пустое значение!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void toolStripMenuItem_GraphUtils_Deep_Click(object sender, EventArgs e)
        {
            bool intIf(Node<int> node) { return node.Data >= 0 && node.Data <= 10; }
            bool stringIf(Node<string> node) { return node.Data.CompareTo("a") == 1 && node.Data.CompareTo("A") == -1; }
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (graphNodeType == 1 && currentIntGraph.Count == 0 || graphNodeType == -1 && currentStringGraph.Count == 0)
                MessageBox.Show("Граф пуст!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
            {
                Form_PickValue pickValue = new Form_PickValue("Node descendants finding", "Введите значение вершины, потомков которой хотите найти");
                pickValue.ShowDialog();
                if (pickValue.value != null && pickValue.value.Length > 0)
                {
                    try
                    {
                        if (graphNodeType == 1)
                        {
                            int value;
                            if (int.TryParse(pickValue.value, out value))
                            {
                                if (GraphUtils<int, int>.FindDeep(currentIntGraph, value, intIf))
                                    MessageBox.Show("Вершина " + value.ToString() + "  и все ее потомки в графе со значениями в диапазоне от 0 до 10!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                                else
                                    MessageBox.Show("Вершина " + value.ToString() + " или ее потомки в графе со значениями вне диапазона от 0 до 10!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                            }
                            else
                                MessageBox.Show("Неверный тип элемента!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                        else
                        {
                            if (GraphUtils<string, int>.FindDeep(currentStringGraph, pickValue.value, stringIf))
                                MessageBox.Show("Вершина " + pickValue.value + "  и все ее потомки в графе со значениями в диапазоне от a до A!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            else
                                MessageBox.Show("Вершина " + pickValue.value + " или ее потомки в графе со значениями вне диапазона от a до A!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                    }
                    catch (DisabledFindGraphException exception)
                    {
                        MessageBox.Show(exception.Message, "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                }
                else
                    MessageBox.Show("Пустое значение!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void toolStripMenuItem_GraphUtils_FindWay_Click(object sender, EventArgs e)
        {
            if (isUnmutable == 0 || graphNodeType == 0)
            {
                MessageBox.Show("Граф еще не инициализирован!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            if (graphNodeType == 1 && currentIntGraph.Count <= 1 || graphNodeType == -1 && currentStringGraph.Count <= 1)
                MessageBox.Show("Граф пуст или содержит один элемент!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            else
            {
                Form_PickValue pickValueNodeFrom = new Form_PickValue("Node picking", "Введите значение вершины, из которой хотите начать путь");
                pickValueNodeFrom.ShowDialog();
                Form_PickValue pickValueNodeTo = new Form_PickValue("Node picking", "Введите значение вершины, в которой хотите закончить путь");
                pickValueNodeTo.ShowDialog();
                int valueNodeFrom, valueNodeTo;
                if (pickValueNodeFrom.value != null && pickValueNodeFrom.value.Length > 0 && pickValueNodeTo.value != null && pickValueNodeTo.value.Length > 0)
                {
                    try
                    {
                        if (graphNodeType == 1)
                        {
                            if (int.TryParse(pickValueNodeFrom.value, out valueNodeFrom) && int.TryParse(pickValueNodeTo.value, out valueNodeTo))
                            {
                                int way = GraphUtils<int, int>.WaveAlgorithm(currentIntGraph, valueNodeFrom, valueNodeTo);
                                MessageBox.Show("Кратчайший путь из вершины " + valueNodeFrom.ToString() + " в вершину " + valueNodeTo.ToString() + " равен " + way.ToString() + "!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                            }
                            else
                                MessageBox.Show("Неверный тип элемента!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                        }
                        else
                        {
                            int way = GraphUtils<string, int>.WaveAlgorithm(currentStringGraph, pickValueNodeFrom.value, pickValueNodeTo.value);
                            MessageBox.Show("Кратчайший путь из вершины " + pickValueNodeFrom.value + " в вершину " + pickValueNodeTo.value + " равен " + way.ToString() + "!", "Успех!", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        }
                    }
                    catch (DisabledFindGraphException exception)
                    {
                        MessageBox.Show(exception.Message, "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                }
                else
                    MessageBox.Show("Пустое значение!", "Предупреждение!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
    }
}