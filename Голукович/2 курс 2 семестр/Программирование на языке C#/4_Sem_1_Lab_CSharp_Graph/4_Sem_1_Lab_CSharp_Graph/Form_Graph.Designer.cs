namespace _4_Sem_1_Lab_CSharp_Graph
{
    partial class Form_Graph
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem_CreateGraph = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_ArrayGraph = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_IntIntArrayGraph = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_StringIntArrayGraph = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_LinkedGraph = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_IntIntLinkedGraph = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_StringIntLinkedGraph = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_GraphActions = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_AddNode = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_RemoveNode = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_ContainsNode = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_AddEdge = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_FindDescendants = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_ShowGraph = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_MakeUnmutableMutable = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_ClearGraph = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_GraphUtils = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_GraphUtils_Exists = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_GraphUtils_FindAll = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_GraphUtils_ForEach = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_GraphUtils_CheckForAll = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_GraphUtils_FindNode = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_GraphUtils_Deep = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_GraphUtils_Width = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem_GraphUtils_FindWay = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(4);
            this.menuStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Visible;
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem_CreateGraph,
            this.toolStripMenuItem_GraphActions,
            this.toolStripMenuItem_GraphUtils});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1178, 28);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // toolStripMenuItem_CreateGraph
            // 
            this.toolStripMenuItem_CreateGraph.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem_ArrayGraph,
            this.toolStripMenuItem_LinkedGraph});
            this.toolStripMenuItem_CreateGraph.Name = "toolStripMenuItem_CreateGraph";
            this.toolStripMenuItem_CreateGraph.Size = new System.Drawing.Size(115, 24);
            this.toolStripMenuItem_CreateGraph.Text = "Создать граф";
            // 
            // toolStripMenuItem_ArrayGraph
            // 
            this.toolStripMenuItem_ArrayGraph.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem_IntIntArrayGraph,
            this.toolStripMenuItem_StringIntArrayGraph});
            this.toolStripMenuItem_ArrayGraph.Name = "toolStripMenuItem_ArrayGraph";
            this.toolStripMenuItem_ArrayGraph.Size = new System.Drawing.Size(209, 26);
            this.toolStripMenuItem_ArrayGraph.Text = "Граф на массиве";
            // 
            // toolStripMenuItem_IntIntArrayGraph
            // 
            this.toolStripMenuItem_IntIntArrayGraph.Name = "toolStripMenuItem_IntIntArrayGraph";
            this.toolStripMenuItem_IntIntArrayGraph.Size = new System.Drawing.Size(150, 26);
            this.toolStripMenuItem_IntIntArrayGraph.Text = "int int";
            this.toolStripMenuItem_IntIntArrayGraph.Click += new System.EventHandler(this.toolStripMenuItem_IntIntArrayGraph_Click);
            // 
            // toolStripMenuItem_StringIntArrayGraph
            // 
            this.toolStripMenuItem_StringIntArrayGraph.Name = "toolStripMenuItem_StringIntArrayGraph";
            this.toolStripMenuItem_StringIntArrayGraph.Size = new System.Drawing.Size(150, 26);
            this.toolStripMenuItem_StringIntArrayGraph.Text = "string int";
            this.toolStripMenuItem_StringIntArrayGraph.Click += new System.EventHandler(this.toolStripMenuItem_StringIntArrayGraph_Click);
            // 
            // toolStripMenuItem_LinkedGraph
            // 
            this.toolStripMenuItem_LinkedGraph.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem_IntIntLinkedGraph,
            this.toolStripMenuItem_StringIntLinkedGraph});
            this.toolStripMenuItem_LinkedGraph.Name = "toolStripMenuItem_LinkedGraph";
            this.toolStripMenuItem_LinkedGraph.Size = new System.Drawing.Size(209, 26);
            this.toolStripMenuItem_LinkedGraph.Text = "Граф на листе";
            // 
            // toolStripMenuItem_IntIntLinkedGraph
            // 
            this.toolStripMenuItem_IntIntLinkedGraph.Name = "toolStripMenuItem_IntIntLinkedGraph";
            this.toolStripMenuItem_IntIntLinkedGraph.Size = new System.Drawing.Size(150, 26);
            this.toolStripMenuItem_IntIntLinkedGraph.Text = "int int";
            this.toolStripMenuItem_IntIntLinkedGraph.Click += new System.EventHandler(this.toolStripMenuItem_IntIntLinkedGraph_Click);
            // 
            // toolStripMenuItem_StringIntLinkedGraph
            // 
            this.toolStripMenuItem_StringIntLinkedGraph.Name = "toolStripMenuItem_StringIntLinkedGraph";
            this.toolStripMenuItem_StringIntLinkedGraph.Size = new System.Drawing.Size(150, 26);
            this.toolStripMenuItem_StringIntLinkedGraph.Text = "string int";
            this.toolStripMenuItem_StringIntLinkedGraph.Click += new System.EventHandler(this.toolStripMenuItem_StringIntLinkedGraph_Click);
            // 
            // toolStripMenuItem_GraphActions
            // 
            this.toolStripMenuItem_GraphActions.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem_AddNode,
            this.toolStripMenuItem_RemoveNode,
            this.toolStripMenuItem_ContainsNode,
            this.toolStripMenuItem_AddEdge,
            this.toolStripMenuItem_FindDescendants,
            this.toolStripMenuItem_ShowGraph,
            this.toolStripMenuItem_MakeUnmutableMutable,
            this.toolStripMenuItem_ClearGraph});
            this.toolStripMenuItem_GraphActions.Name = "toolStripMenuItem_GraphActions";
            this.toolStripMenuItem_GraphActions.Size = new System.Drawing.Size(156, 24);
            this.toolStripMenuItem_GraphActions.Text = "Действия с графом";
            // 
            // toolStripMenuItem_AddNode
            // 
            this.toolStripMenuItem_AddNode.Name = "toolStripMenuItem_AddNode";
            this.toolStripMenuItem_AddNode.Size = new System.Drawing.Size(360, 26);
            this.toolStripMenuItem_AddNode.Text = "Добавить вершину";
            this.toolStripMenuItem_AddNode.Click += new System.EventHandler(this.toolStripMenuItem_AddNode_Click);
            // 
            // toolStripMenuItem_RemoveNode
            // 
            this.toolStripMenuItem_RemoveNode.Name = "toolStripMenuItem_RemoveNode";
            this.toolStripMenuItem_RemoveNode.Size = new System.Drawing.Size(360, 26);
            this.toolStripMenuItem_RemoveNode.Text = "Удалить вершину";
            this.toolStripMenuItem_RemoveNode.Click += new System.EventHandler(this.toolStripMenuItem_RemoveNode_Click);
            // 
            // toolStripMenuItem_ContainsNode
            // 
            this.toolStripMenuItem_ContainsNode.Name = "toolStripMenuItem_ContainsNode";
            this.toolStripMenuItem_ContainsNode.Size = new System.Drawing.Size(360, 26);
            this.toolStripMenuItem_ContainsNode.Text = "Содержится ли вершина";
            this.toolStripMenuItem_ContainsNode.Click += new System.EventHandler(this.toolStripMenuItem_ContainsNode_Click);
            // 
            // toolStripMenuItem_AddEdge
            // 
            this.toolStripMenuItem_AddEdge.Name = "toolStripMenuItem_AddEdge";
            this.toolStripMenuItem_AddEdge.Size = new System.Drawing.Size(360, 26);
            this.toolStripMenuItem_AddEdge.Text = "Добавить ребро";
            this.toolStripMenuItem_AddEdge.Click += new System.EventHandler(this.toolStripMenuItem_AddEdge_Click);
            // 
            // toolStripMenuItem_FindDescendants
            // 
            this.toolStripMenuItem_FindDescendants.Name = "toolStripMenuItem_FindDescendants";
            this.toolStripMenuItem_FindDescendants.Size = new System.Drawing.Size(360, 26);
            this.toolStripMenuItem_FindDescendants.Text = "Найти потомков";
            this.toolStripMenuItem_FindDescendants.Click += new System.EventHandler(this.toolStripMenuItem_FindDescendants_Click);
            // 
            // toolStripMenuItem_ShowGraph
            // 
            this.toolStripMenuItem_ShowGraph.Name = "toolStripMenuItem_ShowGraph";
            this.toolStripMenuItem_ShowGraph.Size = new System.Drawing.Size(360, 26);
            this.toolStripMenuItem_ShowGraph.Text = "Показать граф";
            this.toolStripMenuItem_ShowGraph.Click += new System.EventHandler(this.toolStripMenuItem_ShowGraph_Click);
            // 
            // toolStripMenuItem_MakeUnmutableMutable
            // 
            this.toolStripMenuItem_MakeUnmutableMutable.Name = "toolStripMenuItem_MakeUnmutableMutable";
            this.toolStripMenuItem_MakeUnmutableMutable.Size = new System.Drawing.Size(360, 26);
            this.toolStripMenuItem_MakeUnmutableMutable.Text = "Сделать неизменяемым/изменяемым";
            this.toolStripMenuItem_MakeUnmutableMutable.Click += new System.EventHandler(this.toolStripMenuItem_MakeUnmutableMutable_Click);
            // 
            // toolStripMenuItem_ClearGraph
            // 
            this.toolStripMenuItem_ClearGraph.Name = "toolStripMenuItem_ClearGraph";
            this.toolStripMenuItem_ClearGraph.Size = new System.Drawing.Size(360, 26);
            this.toolStripMenuItem_ClearGraph.Text = "Очистить граф";
            this.toolStripMenuItem_ClearGraph.Click += new System.EventHandler(this.toolStripMenuItem_ClearGraph_Click);
            // 
            // toolStripMenuItem_GraphUtils
            // 
            this.toolStripMenuItem_GraphUtils.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem_GraphUtils_Exists,
            this.toolStripMenuItem_GraphUtils_FindAll,
            this.toolStripMenuItem_GraphUtils_ForEach,
            this.toolStripMenuItem_GraphUtils_CheckForAll,
            this.toolStripMenuItem_GraphUtils_FindNode,
            this.toolStripMenuItem_GraphUtils_FindWay});
            this.toolStripMenuItem_GraphUtils.Name = "toolStripMenuItem_GraphUtils";
            this.toolStripMenuItem_GraphUtils.Size = new System.Drawing.Size(172, 24);
            this.toolStripMenuItem_GraphUtils.Text = "Действия с GraphUtils";
            // 
            // toolStripMenuItem_GraphUtils_Exists
            // 
            this.toolStripMenuItem_GraphUtils_Exists.Name = "toolStripMenuItem_GraphUtils_Exists";
            this.toolStripMenuItem_GraphUtils_Exists.Size = new System.Drawing.Size(258, 26);
            this.toolStripMenuItem_GraphUtils_Exists.Text = "Существует ли вершина";
            this.toolStripMenuItem_GraphUtils_Exists.Click += new System.EventHandler(this.toolStripMenuItem_GraphUtils_Exists_Click);
            // 
            // toolStripMenuItem_GraphUtils_FindAll
            // 
            this.toolStripMenuItem_GraphUtils_FindAll.Name = "toolStripMenuItem_GraphUtils_FindAll";
            this.toolStripMenuItem_GraphUtils_FindAll.Size = new System.Drawing.Size(258, 26);
            this.toolStripMenuItem_GraphUtils_FindAll.Text = "Найти все";
            this.toolStripMenuItem_GraphUtils_FindAll.Click += new System.EventHandler(this.toolStripMenuItem_GraphUtils_FindAll_Click);
            // 
            // toolStripMenuItem_GraphUtils_ForEach
            // 
            this.toolStripMenuItem_GraphUtils_ForEach.Name = "toolStripMenuItem_GraphUtils_ForEach";
            this.toolStripMenuItem_GraphUtils_ForEach.Size = new System.Drawing.Size(258, 26);
            this.toolStripMenuItem_GraphUtils_ForEach.Text = "Для каждого";
            this.toolStripMenuItem_GraphUtils_ForEach.Click += new System.EventHandler(this.toolStripMenuItem_GraphUtils_ForEach_Click);
            // 
            // toolStripMenuItem_GraphUtils_CheckForAll
            // 
            this.toolStripMenuItem_GraphUtils_CheckForAll.Name = "toolStripMenuItem_GraphUtils_CheckForAll";
            this.toolStripMenuItem_GraphUtils_CheckForAll.Size = new System.Drawing.Size(258, 26);
            this.toolStripMenuItem_GraphUtils_CheckForAll.Text = "Проверить все";
            this.toolStripMenuItem_GraphUtils_CheckForAll.Click += new System.EventHandler(this.toolStripMenuItem_GraphUtils_CheckForAll_Click);
            // 
            // toolStripMenuItem_GraphUtils_FindNode
            // 
            this.toolStripMenuItem_GraphUtils_FindNode.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem_GraphUtils_Deep,
            this.toolStripMenuItem_GraphUtils_Width});
            this.toolStripMenuItem_GraphUtils_FindNode.Name = "toolStripMenuItem_GraphUtils_FindNode";
            this.toolStripMenuItem_GraphUtils_FindNode.Size = new System.Drawing.Size(258, 26);
            this.toolStripMenuItem_GraphUtils_FindNode.Text = "Найти вершину";
            // 
            // toolStripMenuItem_GraphUtils_Deep
            // 
            this.toolStripMenuItem_GraphUtils_Deep.Name = "toolStripMenuItem_GraphUtils_Deep";
            this.toolStripMenuItem_GraphUtils_Deep.Size = new System.Drawing.Size(224, 26);
            this.toolStripMenuItem_GraphUtils_Deep.Text = "Обход в глубину";
            this.toolStripMenuItem_GraphUtils_Deep.Click += new System.EventHandler(this.toolStripMenuItem_GraphUtils_Deep_Click);
            // 
            // toolStripMenuItem_GraphUtils_Width
            // 
            this.toolStripMenuItem_GraphUtils_Width.Name = "toolStripMenuItem_GraphUtils_Width";
            this.toolStripMenuItem_GraphUtils_Width.Size = new System.Drawing.Size(224, 26);
            this.toolStripMenuItem_GraphUtils_Width.Text = "Обход в ширину";
            this.toolStripMenuItem_GraphUtils_Width.Click += new System.EventHandler(this.toolStripMenuItem_GraphUtils_Width_Click);
            // 
            // toolStripMenuItem_GraphUtils_FindWay
            // 
            this.toolStripMenuItem_GraphUtils_FindWay.Name = "toolStripMenuItem_GraphUtils_FindWay";
            this.toolStripMenuItem_GraphUtils_FindWay.Size = new System.Drawing.Size(258, 26);
            this.toolStripMenuItem_GraphUtils_FindWay.Text = "Кратчайший путь";
            this.toolStripMenuItem_GraphUtils_FindWay.Click += new System.EventHandler(this.toolStripMenuItem_GraphUtils_FindWay_Click);
            // 
            // Form_Graph
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1178, 639);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form_Graph";
            this.Text = "Directed Acyclic Graph";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private MenuStrip menuStrip1;
        private ToolStripMenuItem toolStripMenuItem_CreateGraph;
        private ToolStripMenuItem toolStripMenuItem_ArrayGraph;
        private ToolStripMenuItem toolStripMenuItem_IntIntArrayGraph;
        private ToolStripMenuItem toolStripMenuItem_StringIntArrayGraph;
        private ToolStripMenuItem toolStripMenuItem_LinkedGraph;
        private ToolStripMenuItem toolStripMenuItem_IntIntLinkedGraph;
        private ToolStripMenuItem toolStripMenuItem_StringIntLinkedGraph;
        private ToolStripMenuItem toolStripMenuItem_GraphActions;
        private ToolStripMenuItem toolStripMenuItem_AddNode;
        private ToolStripMenuItem toolStripMenuItem_RemoveNode;
        private ToolStripMenuItem toolStripMenuItem_ContainsNode;
        private ToolStripMenuItem toolStripMenuItem_AddEdge;
        private ToolStripMenuItem toolStripMenuItem_FindDescendants;
        private ToolStripMenuItem toolStripMenuItem_ShowGraph;
        private ToolStripMenuItem toolStripMenuItem_MakeUnmutableMutable;
        private ToolStripMenuItem toolStripMenuItem_ClearGraph;
        private ToolStripMenuItem toolStripMenuItem_GraphUtils;
        private ToolStripMenuItem toolStripMenuItem_GraphUtils_Exists;
        private ToolStripMenuItem toolStripMenuItem_GraphUtils_FindAll;
        private ToolStripMenuItem toolStripMenuItem_GraphUtils_ForEach;
        private ToolStripMenuItem toolStripMenuItem_GraphUtils_CheckForAll;
        private ToolStripMenuItem toolStripMenuItem_GraphUtils_FindNode;
        private ToolStripMenuItem toolStripMenuItem_GraphUtils_Deep;
        private ToolStripMenuItem toolStripMenuItem_GraphUtils_Width;
        private ToolStripMenuItem toolStripMenuItem_GraphUtils_FindWay;
    }
}