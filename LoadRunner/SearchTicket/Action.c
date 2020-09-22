Action()
{
	
	lr_start_transaction("UC_1_SearchTicket");
	
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
		Original value='129615.524827866zzzHAQipffiDDDDDtAAAcpfQVDf' 
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
		
			lr_think_time(64);
			
			//web_reg_find("Fail=NotFound",
		//"Text=User password was correct",
		//LAST);

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
				"Name=login.x", "Value=66", ENDITEM,
				"Name=login.y", "Value=1", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);
	
		lr_end_transaction("Login",LR_AUTO);
	
		lr_start_transaction("Flights");
	
			web_add_header("Sec-Fetch-User", 
				"?1");
		
			web_add_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(55);
			
			web_reg_find("Fail=NotFound",
		"Text=User has returned to the search page.",
		LAST);

		
			web_url("Search Flights Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("Flights",LR_AUTO);
	
		lr_start_transaction("click_find_flights");
	
			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_header("Sec-Fetch-Dest", 
				"frame");
		
			web_add_header("Sec-Fetch-Mode", 
				"navigate");
		
			web_add_header("Sec-Fetch-Site", 
				"same-origin");
		
			web_add_header("Sec-Fetch-User", 
				"?1");
		
			web_add_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(233);
			
			//web_reg_find("Fail=NotFound",
		//"Text=Flight departing from",
		//LAST);

		
		/*Correlation comment - Do not change!  Original value='020;491;09/15/2020' Name ='outboundFlight' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=outboundFlight",
		"TagName=input",
		"Extract=value",
		"Name=outboundFlight",
		"Type=radio",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		LAST);
		
		web_reg_find("Text=<B>{depart}</B> to <B>{arrive}</B> on <B>{departDate}</B>",
		LAST);

	web_submit_data("reservations.pl", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=depart", "Value={depart}", ENDITEM, 
				"Name=departDate", "Value={departDate}", ENDITEM, 
				"Name=arrive", "Value={arrive}", ENDITEM, 
				"Name=returnDate", "Value={returnDate}", ENDITEM, 
				"Name=numPassengers", "Value=1", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=findFlights.x", "Value=58", ENDITEM, 
				"Name=findFlights.y", "Value=10", ENDITEM, 
				"Name=.cgifields", "Value=roundtrip", ENDITEM, 
				"Name=.cgifields", "Value=seatType", ENDITEM, 
				"Name=.cgifields", "Value=seatPref", ENDITEM, 
				LAST);
	
		lr_end_transaction("click_find_flights",LR_AUTO);
	
		lr_start_transaction("select_flight");
	
			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"frame");
		
			web_add_auto_header("Sec-Fetch-Mode", 
				"navigate");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"same-origin");
		
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(90);
			
			//web_reg_find("Fail=NotFound",
		//"Text=Credit Card",
		//LAST);

		//web_reg_find("Text=name=\"firstName\" value=\"{login}\"",
		//LAST);

		
			web_submit_data("reservations.pl_2",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t5.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=reserveFlights.x", "Value=43", ENDITEM,
		"Name=reserveFlights.y", "Value=7", ENDITEM,
		LAST);
	
		lr_end_transaction("select_flight",LR_AUTO);
	
		lr_start_transaction("Logout");
	
			web_revert_auto_header("Sec-Fetch-User");
		
			lr_think_time(37);
			
			web_reg_find("Fail=NotFound",
		"Text= A Session ID has been created and loaded into a cookie called MSO.",
		LAST);

		
			web_url("welcome.pl", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t6.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("Logout",LR_AUTO);

	lr_end_transaction("UC_1_SearchTicket",LR_AUTO);

	return 0;
}