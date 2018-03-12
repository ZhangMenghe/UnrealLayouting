// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using System;
public class AutoLayout : ModuleRules
{
	public AutoLayout(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		//PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "RHI", "RenderCore", "ShaderCore" });
        //loadtest();
        LoadOpenCV(Target);

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../ThirdParty/")); }
    }
    //private string[] libname;
    public bool LoadOpenCV(ReadOnlyTargetRules Target)
    {
        //libname = new string[] { "opencv_core340.lib", "opencv_imgproc340.lib" };
        // Start OpenCV linking here!
        bool isLibrarySupported = false;

        // Create OpenCV Path 
        string OpenCVPath = Path.Combine(ThirdPartyPath, "OpenCV");

        // Get Library Path 
        string LibPath = "";
        bool isdebug = Target.Configuration == UnrealTargetConfiguration.Debug && BuildConfiguration.bDebugBuildsActuallyUseDebugCRT;
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            LibPath = Path.Combine(OpenCVPath, "Libraries", "Win64");
            isLibrarySupported = true;
        }
        else
        {
            string Err = string.Format("{0} dedicated server is made to depend on {1}. We want to avoid this, please correct module dependencies.", Target.Platform.ToString(), this.ToString()); System.Console.WriteLine(Err);
        }

        if (isLibrarySupported)
        {
            //Add Include path 
            PublicIncludePaths.AddRange(new string[] { Path.Combine(OpenCVPath, "Includes") });

            // Add Library Path 
            PublicLibraryPaths.Add(LibPath);

            //Add Static Libraries
            PublicAdditionalLibraries.Add("opencv_core340.lib");
            PublicAdditionalLibraries.Add("opencv_imgproc340.lib");
            PublicAdditionalLibraries.Add("opencv_core340d.lib");
            PublicAdditionalLibraries.Add("opencv_imgproc340d.lib");
            //Add Dynamic Libraries
            PublicDelayLoadDLLs.Add("opencv_core340.dll");
            PublicDelayLoadDLLs.Add("opencv_imgproc340.dll");
            PublicDelayLoadDLLs.Add("opencv_core340d.dll");
            PublicDelayLoadDLLs.Add("opencv_imgproc340d.dll");
/*
            string path = @LibPath + "/lib.txt";
            Console.WriteLine(path);
   try
   {
       if (!File.Exists(path))
       {
           Console.WriteLine("lib not exist");
       }

       using (StreamReader sr = new StreamReader(path))
       {
           while (sr.Peek() >= 0)
               //Console.WriteLine(sr.ReadLine());
               PublicAdditionalLibraries.Add(sr.ReadLine());
       }
   }
   catch (Exception e)
   {
       Console.WriteLine("The process failed: {0}", e.ToString());
   }

   path = @LibPath + "/dll.txt";
   try
   {
       if (!File.Exists(path))
       {
           Console.WriteLine("dll not exist");
       }

       using (StreamReader sr = new StreamReader(path))
       {
           while (sr.Peek() >= 0)
               //Console.WriteLine(sr.ReadLine());
               PublicDelayLoadDLLs.Add(sr.ReadLine());
       }
   }
   catch (Exception e)
   {
       Console.WriteLine("The process failed: {0}", e.ToString());
   }*/

        }

        Definitions.Add(string.Format("WITH_OPENCV_BINDING={0}", isLibrarySupported ? 1 : 0));

        return isLibrarySupported;
    }
}
