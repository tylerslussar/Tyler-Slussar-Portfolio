﻿#pragma checksum "..\..\ManagerAccessWindow.xaml" "{8829d00f-11b8-4213-878b-770e8597ac16}" "EDAE85F732CB1B6ACE17299EBA041217D4521BFEA44CB481083864512ECDFF75"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using CapitalUAirlines;
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;


namespace CapitalUAirlines {
    
    
    /// <summary>
    /// ManagerAccessWindow
    /// </summary>
    public partial class ManagerAccessWindow : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 21 "..\..\ManagerAccessWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button logOut;
        
        #line default
        #line hidden
        
        
        #line 25 "..\..\ManagerAccessWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox flightNumber;
        
        #line default
        #line hidden
        
        
        #line 26 "..\..\ManagerAccessWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button seatPlan;
        
        #line default
        #line hidden
        
        
        #line 27 "..\..\ManagerAccessWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button genReport;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/CapitalUAirlines;component/manageraccesswindow.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\ManagerAccessWindow.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.logOut = ((System.Windows.Controls.Button)(target));
            
            #line 21 "..\..\ManagerAccessWindow.xaml"
            this.logOut.Click += new System.Windows.RoutedEventHandler(this.LogOut_Click);
            
            #line default
            #line hidden
            return;
            case 2:
            this.flightNumber = ((System.Windows.Controls.TextBox)(target));
            return;
            case 3:
            this.seatPlan = ((System.Windows.Controls.Button)(target));
            
            #line 26 "..\..\ManagerAccessWindow.xaml"
            this.seatPlan.Click += new System.Windows.RoutedEventHandler(this.SeatPlan_Click);
            
            #line default
            #line hidden
            return;
            case 4:
            this.genReport = ((System.Windows.Controls.Button)(target));
            
            #line 27 "..\..\ManagerAccessWindow.xaml"
            this.genReport.Click += new System.Windows.RoutedEventHandler(this.GenReport_Click);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}
