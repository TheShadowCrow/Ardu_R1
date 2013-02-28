Core_Protecol_Handler::Core_Protecol_Handler(void *HeadFunction, void *Movement, void *Sonar)
{
	Head = HeadFunction;
	Move = Movement;
	Sence = Sonar;
}


Core_Protocol_Handler::Node(string node, string[] labels)
{
	for(i =0; i <devicenode; i++)
	{
		switch(node)
		{
			case "movement":
				&Move((int)labels[0]);
				break;
			case "head":
				if(labels[0] == "sweep")
				{
				
				}
				else
				{
					&Head((int)labels[0]);
				}
		
		}
}