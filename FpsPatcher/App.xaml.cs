﻿using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using FPSPatcher.Views;


namespace FPSPatcher {
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application {

        private MainWindow mainWindow;

        private void App_OnStartup(object sender, StartupEventArgs e) {
            mainWindow = new MainWindow {DataContext = FindResource("MainViewModel")};
            mainWindow.Show();
        }
    }
}
