'==========================================================================
'
'  File:        FormBomsSet.vb
'  Location:    TopACE.BomsSetEditor <Visual Basic .Net>
'  Description: TopACE .SET爆炸脚本编辑器
'  Version:     2009.01.02.
'  Copyright(C) F.R.C.
'
'==========================================================================

Imports System
Imports System.IO
Imports System.Data
Imports System.Windows.Forms
Imports Microsoft.VisualBasic
Imports Firefly
Imports Firefly.GUI

Public Class FormBomsSet

    Private Sub FormBomsSet_Shown(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Shown
        FileSelectBox.Path = My.Settings.Path
    End Sub

    Private Sub FormBomsSet_FormClosed(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        My.Settings.Path = FileSelectBox.Path
    End Sub

    Private Index As Integer = 1
    Private Sub DataGridView_RowEnter(ByVal sender As Object, ByVal e As System.Windows.Forms.DataGridViewCellEventArgs) Handles DataGridView.RowEnter
        If DataGridView.Item(PnumColumn.Index, e.RowIndex).Value Is Nothing Then
            DataGridView.Item(PnumColumn.Index, e.RowIndex).Value = Index
            Index += 1
        End If
    End Sub

    Private Sub DataGridView_DataError(ByVal sender As Object, ByVal e As System.Windows.Forms.DataGridViewDataErrorEventArgs) Handles DataGridView.DataError
        ErrorProvider.SetError(DataGridView.EditingControl, e.Exception.Message)
        ErrorProvider.SetIconAlignment(DataGridView.EditingControl, ErrorIconAlignment.MiddleLeft)
        ErrorProvider.SetIconPadding(DataGridView.EditingControl, -20)
    End Sub

    Private Sub DataGridView_CellEndEdit(ByVal sender As Object, ByVal e As System.Windows.Forms.DataGridViewCellEventArgs) Handles DataGridView.CellEndEdit
        ErrorProvider.Clear()
    End Sub

    Private Sub Button_Open_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Open.Click
        If FileSelectBox.Path = "" Then
            FileSelectBox.IsSaveDialog = False
            FileSelectBox.PopupDialog()
        End If
        If FileSelectBox.Path = "" Then Return

        Dim Path As String = FileSelectBox.Path
        Using s As New StreamEx(Path, FileMode.Open, FileAccess.Read)
            If s.ReadSimpleString(4) <> "SET" Then Throw New InvalidDataException
            Dim Count = s.ReadInt32

            BomsSet.BomsTable.RejectChanges()
            BomsSet.Clear()

            Index = 1

            For n = 0 To Count - 1
                Dim row = BomsSet.BomsTable.NewRow
                s.ReadInt32()
                row.Item(PnumColumn.Index) = Index
                Index += 1
                row.Item(RandomSizeMINColumn.Index) = s.ReadInt32
                row.Item(RandomSizeMAXColumn.Index) = s.ReadInt32
                row.Item(RandomMoveMINColumn.Index) = s.ReadInt32
                row.Item(RandomMoveMAXColumn.Index) = s.ReadInt32
                row.Item(ShowTimeStartColumn.Index) = s.ReadInt32
                row.Item(ShowTimeEndColumn.Index) = s.ReadInt32
                BomsSet.BomsTable.AddBomsTableRow(row)
            Next

            BomsSet.BomsTable.AcceptChanges()
        End Using
    End Sub

    Private Sub Button_Save_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Save.Click
        If FileSelectBox.Path = "" Then
            FileSelectBox.IsSaveDialog = True
            FileSelectBox.PopupDialog()
            FileSelectBox.IsSaveDialog = False
        End If
        If FileSelectBox.Path = "" Then Return

        Dim Path As String = FileSelectBox.Path
        Using s As New StreamEx(Path, FileMode.Create, FileAccess.ReadWrite)
            BomsSet.BomsTable.AcceptChanges()

            s.WriteSimpleString("SET", 4)
            s.WriteInt32(BomsSet.BomsTable.Count)

            For Each row As DataRow In BomsSet.BomsTable.Rows
                s.WriteInt32(CUS(0UI))
                s.WriteInt32(row.Item(RandomSizeMINColumn.Index))
                s.WriteInt32(row.Item(RandomSizeMAXColumn.Index))
                s.WriteInt32(row.Item(RandomMoveMINColumn.Index))
                s.WriteInt32(row.Item(RandomMoveMAXColumn.Index))
                s.WriteInt32(row.Item(ShowTimeStartColumn.Index))
                s.WriteInt32(row.Item(ShowTimeEndColumn.Index))
            Next
        End Using
    End Sub

    Private Sub DataGridView_RowValidated(ByVal sender As Object, ByVal e As System.Windows.Forms.DataGridViewCellEventArgs) Handles DataGridView.RowValidated
        If BomsSet.BomsTable.Rows.Count <= e.RowIndex Then Return
        Dim row = BomsSet.BomsTable.Rows.Item(e.RowIndex)
        If row.Item(RandomSizeMINColumn.Index) > row.Item(RandomSizeMAXColumn.Index) Then
            row.RowError = "随机大小最小值大于最大值"
        ElseIf row.Item(RandomMoveMINColumn.Index) > row.Item(RandomMoveMAXColumn.Index) Then
            row.RowError = "随机移动最小值大于最大值"
        ElseIf row.Item(ShowTimeStartColumn.Index) > row.Item(ShowTimeEndColumn.Index) Then
            row.RowError = "开始时间大于结束时间"
        Else
            row.RowError = ""
        End If
    End Sub
End Class
