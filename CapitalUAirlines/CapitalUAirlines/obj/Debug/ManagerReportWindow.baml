   M S B A M L   `   `   `  ????K  GCapitalUAirlines, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null3clr-namespace:CapitalUAirlinesCapitalUAirlines  5   	   *    $CapitalUAirlines.ManagerReportWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   0localclr-namespace:CapitalUAirlines     5   	     ? Title$  ManagerReportWindow??5   	   $	??800??6%   $
??1100??62    ? WindowStartupLocation$ CenterScreen=?6?    ? 	Resources 5	         ColumnHeaderStyle ?? 
TargetType=  7System.Windows.Controls.Primitives.DataGridColumnHeader ?? Property ?? Value ?? TextAlignment??%  &	        ?? 5
   
   "  6*   .?5      ??  ? ?? 5      ?? 5      .R?5      ?? $??	Underline{?65   $
??Wrap=?6Q   $??20(?6e   $??Arial)?6s   $ Center=?6?   ??6$   ?? 6?   5      5      ?? 5       ? ??$ Center=?6;   5      5      .??5      ?  ? RowDefinitions 5   
   ?? 5      $??* ?6   ?? 5      $??70 ?6   .+?5   
   ?? -   5         ??Name$ close??5      $??1??6   $??Close??6-   $??30(?6=   $??Right=?6K   $??5q?6g   $	??150??6r   6~   &   System.Windows.Controls.DataGrid  5   
   -   5        	  Name$	 
reportGrid??5      $??0??6'   $??0??64   $??3??6D   $
??Auto??6p   $
??Auto??6}   
   
IsReadOnly
 .    CanUserSortColumns .     AreRowDetailsFrozen .    CanUserReorderColumns .     CanUserResizeColumns .     CanUserAddRows .     AutoGenerateColumns .  
??????    RowBackground
 ?????   AlternatingRowBackground
 ?????$??Center=?5      $	??Top=?60   ??. $
??Auto=?6m   ??5   X   ??    Columns 5      0  *System.Windows.Controls.DataGridTextColumn  5!      ,  &System.Windows.Controls.DataGridColumn   Header$ Passengers/Seats??6%      HeaderStyle# [  6?      FontSize$ 20Q?5#   %      
IsReadOnly .    Width5  /System.Windows.Controls.DataGridLengthConverter$ 4* 6E      
Visibility$ Visible=?6P   1  +System.Windows.Controls.DataGridBoundColumn   Binding 5"   %   ??  ?? Path$ passengerNames? ?? Mode$ OneWay=? ?? UpdateSourceTrigger$ PropertyChanged=?   ElementStyle 5$      ?? 5%      " ??6    .?5&      ??  ?@??TextAlignment$ Center=?6>   5'      5)        5+      $ Group Number??6%   # [  6;   $ 20Q?5-   %    . $ * 6E   $ Visible=?6O    5,   %   ?? $ groupNumber?$ OneWay=?$ PropertyChanged=? ?? StringFormat$ 
Group: {0}?? 5.      ?? 5/      " ??6    .?50      ??  ?@??TextAlignment$ Center=?6>   51      53        55      $ Group Category??6%   # [  6=   $ 20Q?57   %    . $ * 6E   $ Visible=?6O    56   %   ?? $ groupCategory?$ OneWay=?$ PropertyChanged=? 58      ?? 59      " ??6    .?5:      ??  ?@??TextAlignment$ Center=?6>   5;      5=        5?      $ Satisfaction Score??6%   # [  6A   $ 20Q?5A   %    . $ * 6E   $ Visible=?6O    5@   %   ?? $ groupSatisfactionScore?$ OneWay=?$ PropertyChanged=? 5B      ?? 5C      " ??6    .?5D      ??  ?@??TextAlignment$ Center=?6>   5E      5G      5J      5K      5L      