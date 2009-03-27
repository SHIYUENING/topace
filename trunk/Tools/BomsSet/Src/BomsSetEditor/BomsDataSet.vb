

Partial Public Class BomsDataSet
    Partial Class BomsTableDataTable

        Private Sub BomsTableDataTable_ColumnChanging(ByVal sender As System.Object, ByVal e As System.Data.DataColumnChangeEventArgs) Handles Me.ColumnChanging
            If (e.Column.ColumnName = Me.RandomSizeMAXColumn.ColumnName) Then
                '在此处添加用户代码
            End If

        End Sub

    End Class

End Class
