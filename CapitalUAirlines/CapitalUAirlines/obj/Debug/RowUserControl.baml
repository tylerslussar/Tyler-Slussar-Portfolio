   M S B A M L   `   `   `  ????K  GCapitalUAirlines, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null3clr-namespace:CapitalUAirlinesCapitalUAirlines  5      %    CapitalUAirlines.RowUserControl   5      \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5      @d2http://schemas.microsoft.com/expression/blend/2008     5      0localclr-namespace:CapitalUAirlines     5      
???????  ? 	Resources  5	      .  (CapitalUAirlines.BooleanToColorConverter   ColorConverter  	seatStyle ?? 
TargetType ?? Property ?? Value??%5  &	        &	        5
   
   6(   ?? 5   
   " ??6"   .?5      ??  ? ??$ Center=?64   ?? 5       ? ??$ Center=?62   ?? 5       ? ??
 ?   ?6,   ?? 5       ? ??$ 1q?60   ?? 5       ?@??
IsReadOnly . 6+   ?? 5       ? ??$ 70??6&   5      5      .??5      ?  ? ColumnDefinitions 5   
   ?? 5      $	??.5* ?6   ?? 5      $??* ?6   ?? 5      $??* ?6   ?? 5      $??* ?6   ?? 5      $??* ?6   ?? 5      $??* ?6   ?? 5      $??* ?6   ?? 5      $??* ?6   .+?5   
   ?? $??0??6   $??Center=?6$   $??Center=?6A   $??25(?6\   ??6j   ?? *	rowNumber+?? 5    
   $??1??6   $	??120??6"   $??30??6.   #??[ 6:   ??6]   ?? *seats[0].isTaken+ ?? Mode$ OneWay=? ?? UpdateSourceTrigger$ PropertyChanged=? ?? 	Converter# [  ?? 5!   
   $??2??6   $	??120??6"   $??30??6.   #??[ 6:   ??6]   ?? *seats[1].isTaken+$ OneWay=?$ PropertyChanged=?# [  ?? 5"   
   $??3??6   $	??120??6"   $??30??6.   #??[ 6:   ??6]   ?? *seats[2].isTaken+$ OneWay=?$ PropertyChanged=?# [  ?? 5#   
   $??5??6   $	??120??6"   $??30??6.   #??[ 6:   ??6]   ?? *seats[3].isTaken+$ OneWay=?$ PropertyChanged=?# [  ?? 5$   
   $??6??6   $	??120??6"   $??30??6.   #??[ 6:   ??6]   ?? *seats[4].isTaken+$ OneWay=?$ PropertyChanged=?# [  ?? 5%   
   $??7??6   $	??120??6"   $??30??6.   #??[ 6:   ??6]   ?? *seats[5].isTaken+$ OneWay=?$ PropertyChanged=?# [  5&      5'      