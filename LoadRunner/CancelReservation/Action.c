Action()
{
int flight_id_num = 0;
	lr_start_transaction("UC_3_CancelReservation");
	
		lr_start_transaction("GotoSite");

	
			web_set_sockets_option("SSL_VERSION", "AUTO");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"none");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"document");
		
			web_add_auto_header("Sec-Fetch-Mode", 
				"navigate");
		
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
		/*Correlation comment: Automatic rules - Do not change!  
		Original value='129616.867719725zzzHVzHpzDDDDDDDtAAADpAAfi' 
		Name ='userSession' 
		Type ='Rule' 
		AppName ='WebTours' 
		RuleName ='UserSession'*/
			web_reg_save_param_attrib(
				"ParamName=userSession",
				"TagName=input",
				"Extract=value",
				"Name=userSession",
				"Type=hidden",
				SEARCH_FILTERS,
				"RequestUrl=*/nav.pl*",
				LAST);
				
				web_reg_find("Fail=NotFound",
					"Text=A Session ID has been created and loaded into a cookie called MSO.",
					LAST);
		
			web_url("WebTours", 
				"URL=http://localhost:1080/WebTours", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=", 
				"Snapshot=t1.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("GotoSite", LR_AUTO);
	
	
		lr_start_transaction("Login");

			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"frame");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"same-origin");
		
			lr_think_time(22);
			
			web_reg_find("Text=Welcome, <b>{login}</b>",
		LAST);
			
			web_submit_data("login.pl",
				"Action=http://localhost:1080/cgi-bin/login.pl",
				"Method=POST",
				"TargetFrame=body",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
				"Snapshot=t2.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=userSession", "Value={userSession}", ENDITEM,
				"Name=username", "Value={login}", ENDITEM,
				"Name=password", "Value={password}", ENDITEM,
				"Name=login.x", "Value=64", ENDITEM,
				"Name=login.y", "Value=11", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);

		lr_end_transaction("Login",LR_AUTO);
	
		lr_start_transaction("watch_itinerary");

			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(60);
			
			web_reg_save_param("flight_id",
		"LB=name=\"flightID\" value=\"",
		"RB=\"",
		"Ord=ALL",
		LAST);
			
			web_reg_find("Fail=NotFound",
		"Text=User wants the intineraries.",
		LAST);

		
	web_url("Itinerary Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);

			flight_id_num = atoi(lr_eval_string("{flight_id_count}"));
			
		lr_end_transaction("watch_itinerary",LR_AUTO);
		
		
	
		lr_start_transaction("delete_ticket");

			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(52);
			
			//web_reg_find("Fail=NotFound",
			//	"Text=Itinerary",
			//	LAST);
			
			//name="flightID" value="45707506-821-JB"
			
	//		web_reg_save_param("flight_id_2",
	//	"LB=name=\"flightID\" value=\"",
	//	"RB=\"",
	//	"Ord=ALL",
	//	LAST);

	web_reg_save_param("flight_numbers",
		"LB=<b>A total of ",
		"RB=scheduled flights.</font></b>",
		LAST);

		
	
			web_submit_form("web_submit_form",
			ITEMDATA,
			"Name=1", "Value=on", ENDITEM,
			 "Name=removeFlights.x", "Value=73", ENDITEM,
			"Name=removeFlights.y", "Value=8", ENDITEM,
			EXTRARES,
			"URL=http://localhost:1080/cgi-bin/itinerary.pl", "Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
			LAST);

			if(atoi(lr_eval_string("{flight_numbers}")) > flight_id_num){
			
				lr_error_message("itinerary not deleted");
			}else {

	lr_output_message("itinerary deleted");
			}

		
		
			web_submit_data("itinerary.pl",
		"Action=http://localhost:1080/cgi-bin/itinerary.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl",
		"Snapshot=t4.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=1", "Value=on", ENDITEM,
		"Name=flightID", "Value=45712672-780-JB", ENDITEM,
		"Name=flightID", "Value=45712672-1549-JB", ENDITEM,
		"Name=flightID", "Value=49037506-2360-jb", ENDITEM,
		"Name=flightID", "Value=49037506-3129-jb", ENDITEM,
		"Name=removeFlights.x", "Value=73", ENDITEM,
		"Name=removeFlights.y", "Value=8", ENDITEM,
		"Name=.cgifields", "Value=4", ENDITEM,
		"Name=.cgifields", "Value=1", ENDITEM,
		"Name=.cgifields", "Value=3", ENDITEM,
		"Name=.cgifields", "Value=2", ENDITEM,
		LAST);

		lr_end_transaction("delete_ticket",LR_AUTO);
	
		lr_start_transaction("Logout");
		
			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_header("Sec-Fetch-User", 
				"?1");
		
			lr_think_time(28);
			
			web_reg_find("Fail=NotFound",
				"Text= A Session ID has been created and loaded into a cookie called MSO.",
				LAST);
		
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				LAST);

		lr_end_transaction("Logout",LR_AUTO);

	lr_end_transaction("UC_3_CancelReservation",LR_AUTO);

	return 0;
}