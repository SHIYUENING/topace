<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class FormBomsSet
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim DataGridViewCellStyle3 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle
        Dim DataGridViewCellStyle4 As System.Windows.Forms.DataGridViewCellStyle = New System.Windows.Forms.DataGridViewCellStyle
        Me.DataGridView = New System.Windows.Forms.DataGridView
        Me.PnumColumn = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.RandomSizeMINColumn = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.RandomSizeMAXColumn = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.RandomMoveMINColumn = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.RandomMoveMAXColumn = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.ShowTimeStartColumn = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.ShowTimeEndColumn = New System.Windows.Forms.DataGridViewTextBoxColumn
        Me.BomsSetBindingSource = New System.Windows.Forms.BindingSource(Me.components)
        Me.BomsSet = New BomsSet.BomsDataSet
        Me.Button_Open = New System.Windows.Forms.Button
        Me.FileSelectBox = New Firefly.GUI.FileSelectBox
        Me.Button_Save = New System.Windows.Forms.Button
        Me.ErrorProvider = New System.Windows.Forms.ErrorProvider(Me.components)
        CType(Me.DataGridView, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.BomsSetBindingSource, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.BomsSet, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.ErrorProvider, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'DataGridView
        '
        DataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight
        DataGridViewCellStyle3.Format = "N0"
        Me.DataGridView.AlternatingRowsDefaultCellStyle = DataGridViewCellStyle3
        Me.DataGridView.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
                    Or System.Windows.Forms.AnchorStyles.Left) _
                    Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.DataGridView.AutoGenerateColumns = False
        Me.DataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill
        Me.DataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.DataGridView.Columns.AddRange(New System.Windows.Forms.DataGridViewColumn() {Me.PnumColumn, Me.RandomSizeMINColumn, Me.RandomSizeMAXColumn, Me.RandomMoveMINColumn, Me.RandomMoveMAXColumn, Me.ShowTimeStartColumn, Me.ShowTimeEndColumn})
        Me.DataGridView.DataMember = "BomsTable"
        Me.DataGridView.DataSource = Me.BomsSetBindingSource
        DataGridViewCellStyle4.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleRight
        DataGridViewCellStyle4.BackColor = System.Drawing.SystemColors.Window
        DataGridViewCellStyle4.Font = New System.Drawing.Font("宋体", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        DataGridViewCellStyle4.ForeColor = System.Drawing.SystemColors.ControlText
        DataGridViewCellStyle4.Format = "N0"
        DataGridViewCellStyle4.SelectionBackColor = System.Drawing.SystemColors.Highlight
        DataGridViewCellStyle4.SelectionForeColor = System.Drawing.SystemColors.HighlightText
        DataGridViewCellStyle4.WrapMode = System.Windows.Forms.DataGridViewTriState.[False]
        Me.DataGridView.DefaultCellStyle = DataGridViewCellStyle4
        Me.DataGridView.Location = New System.Drawing.Point(-1, 41)
        Me.DataGridView.Name = "DataGridView"
        Me.DataGridView.RowTemplate.Height = 23
        Me.DataGridView.Size = New System.Drawing.Size(664, 372)
        Me.DataGridView.TabIndex = 0
        '
        'PnumColumn
        '
        Me.PnumColumn.DataPropertyName = "Pnum"
        Me.PnumColumn.HeaderText = "索引"
        Me.PnumColumn.Name = "PnumColumn"
        Me.PnumColumn.ReadOnly = True
        '
        'RandomSizeMINColumn
        '
        Me.RandomSizeMINColumn.DataPropertyName = "RandomSizeMIN"
        Me.RandomSizeMINColumn.HeaderText = "随机大小最小值"
        Me.RandomSizeMINColumn.Name = "RandomSizeMINColumn"
        '
        'RandomSizeMAXColumn
        '
        Me.RandomSizeMAXColumn.DataPropertyName = "RandomSizeMAX"
        Me.RandomSizeMAXColumn.HeaderText = "随机大小最大值"
        Me.RandomSizeMAXColumn.Name = "RandomSizeMAXColumn"
        '
        'RandomMoveMINColumn
        '
        Me.RandomMoveMINColumn.DataPropertyName = "RandomMoveMIN"
        Me.RandomMoveMINColumn.HeaderText = "随机移动量最小值"
        Me.RandomMoveMINColumn.Name = "RandomMoveMINColumn"
        '
        'RandomMoveMAXColumn
        '
        Me.RandomMoveMAXColumn.DataPropertyName = "RandomMoveMAX"
        Me.RandomMoveMAXColumn.HeaderText = "随机移动量最大值"
        Me.RandomMoveMAXColumn.Name = "RandomMoveMAXColumn"
        '
        'ShowTimeStartColumn
        '
        Me.ShowTimeStartColumn.DataPropertyName = "ShowTimeStart"
        Me.ShowTimeStartColumn.HeaderText = "开始时间"
        Me.ShowTimeStartColumn.Name = "ShowTimeStartColumn"
        '
        'ShowTimeEndColumn
        '
        Me.ShowTimeEndColumn.DataPropertyName = "ShowTimeEnd"
        Me.ShowTimeEndColumn.HeaderText = "结束时间"
        Me.ShowTimeEndColumn.Name = "ShowTimeEndColumn"
        '
        'BomsSetBindingSource
        '
        Me.BomsSetBindingSource.DataSource = Me.BomsSet
        Me.BomsSetBindingSource.Position = 0
        '
        'BomsSet
        '
        Me.BomsSet.DataSetName = "BomsSet"
        Me.BomsSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema
        '
        'Button_Open
        '
        Me.Button_Open.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.Button_Open.Location = New System.Drawing.Point(541, 10)
        Me.Button_Open.Name = "Button_Open"
        Me.Button_Open.Size = New System.Drawing.Size(51, 23)
        Me.Button_Open.TabIndex = 1
        Me.Button_Open.Text = "打开"
        Me.Button_Open.UseVisualStyleBackColor = True
        '
        'FileSelectBox
        '
        Me.FileSelectBox.AutoSize = True
        Me.FileSelectBox.Filter = "(*.set)|*.set"
        Me.FileSelectBox.LabelText = "set文件"
        Me.FileSelectBox.Location = New System.Drawing.Point(12, 7)
        Me.FileSelectBox.ModeSelection = Firefly.GUI.FileDialogEx.ModeSelectionEnum.File
        Me.FileSelectBox.Name = "FileSelectBox"
        Me.FileSelectBox.Path = ""
        Me.FileSelectBox.Size = New System.Drawing.Size(523, 28)
        Me.FileSelectBox.SplitterDistance = 45
        Me.FileSelectBox.TabIndex = 2
        '
        'Button_Save
        '
        Me.Button_Save.Anchor = CType((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.Button_Save.Location = New System.Drawing.Point(598, 10)
        Me.Button_Save.Name = "Button_Save"
        Me.Button_Save.Size = New System.Drawing.Size(51, 23)
        Me.Button_Save.TabIndex = 1
        Me.Button_Save.Text = "保存"
        Me.Button_Save.UseVisualStyleBackColor = True
        '
        'ErrorProvider
        '
        Me.ErrorProvider.BlinkRate = 0
        Me.ErrorProvider.BlinkStyle = System.Windows.Forms.ErrorBlinkStyle.NeverBlink
        Me.ErrorProvider.ContainerControl = Me
        '
        'FormBomsSet
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(662, 410)
        Me.Controls.Add(Me.FileSelectBox)
        Me.Controls.Add(Me.Button_Save)
        Me.Controls.Add(Me.Button_Open)
        Me.Controls.Add(Me.DataGridView)
        Me.Name = "FormBomsSet"
        Me.Text = "TopACE .SET爆炸脚本编辑器"
        CType(Me.DataGridView, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.BomsSetBindingSource, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.BomsSet, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.ErrorProvider, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents DataGridView As System.Windows.Forms.DataGridView
    Friend WithEvents Button_Open As System.Windows.Forms.Button
    Friend WithEvents BomsSet As BomsSet.BomsDataSet
    Friend WithEvents BomsSetBindingSource As System.Windows.Forms.BindingSource
    Friend WithEvents FileSelectBox As Firefly.GUI.FileSelectBox
    Friend WithEvents Button_Save As System.Windows.Forms.Button
    Friend WithEvents PnumColumn As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents RandomSizeMINColumn As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents RandomSizeMAXColumn As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents RandomMoveMINColumn As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents RandomMoveMAXColumn As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents ShowTimeStartColumn As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents ShowTimeEndColumn As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents ErrorProvider As System.Windows.Forms.ErrorProvider

End Class
