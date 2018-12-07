#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
//#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"

//#include "ns3/netanim-module.h"//////////////////


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SecondScriptExample");

int
main(int argc, char *argv[])
{
	bool verbose = true;
	uint32_t nCsma = 3;
	// uint32_t nFlows = 2;
	 //uint16_t port = 50000;

	CommandLine cmd;
	//cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
	cmd.AddValue("verbose", "Tell echo applications to log if true", verbose);

	cmd.Parse(argc, argv);


	LogComponentEnable("PacketSink", LOG_LEVEL_INFO);
	LogComponentEnable("OnOffApplication", LOG_LEVEL_INFO);


	nCsma = nCsma == 0 ? 1 : nCsma;

	//创建底层的4个小网络
	NodeContainer csmaNodes1;
	csmaNodes1.Create(3);
	NodeContainer csmaNodes2;
	csmaNodes2.Create(3);
	NodeContainer csmaNodes3;
	csmaNodes3.Create(3);
	NodeContainer csmaNodes4;
	csmaNodes4.Create(3);


	//创建上层的csma中左侧网络
	NodeContainer csmaNodes5;
	csmaNodes5.Create(1);
	csmaNodes5.Add(csmaNodes1.Get(0));
	csmaNodes5.Add(csmaNodes2.Get(0));
	//创建上层的csma中右侧网络  
	NodeContainer csmaNodes6;
	csmaNodes6.Create(1);
	csmaNodes6.Add(csmaNodes3.Get(0));
	csmaNodes6.Add(csmaNodes4.Get(0));
	//创建总的csma大网络  
	NodeContainer csmaNodes7;
	csmaNodes7.Create(1);
	csmaNodes7.Add(csmaNodes5.Get(0));
	csmaNodes7.Add(csmaNodes6.Get(0));

	//CMSA1网络拓扑
	CsmaHelper csma1;
	csma1.SetChannelAttribute("DataRate", StringValue("1.0Mbps"));
	csma1.SetChannelAttribute("Delay", TimeValue(NanoSeconds(500)));

	NetDeviceContainer csmaDevices1;
	csmaDevices1 = csma1.Install(csmaNodes1);
	//CMSA2网络拓扑
	CsmaHelper csma2;
	csma2.SetChannelAttribute("DataRate", StringValue("1.0Mbps"));
	csma2.SetChannelAttribute("Delay", TimeValue(NanoSeconds(500)));

	NetDeviceContainer csmaDevices2;
	csmaDevices2 = csma2.Install(csmaNodes2);
	//CMSA3网络拓扑
	CsmaHelper csma3;
	csma3.SetChannelAttribute("DataRate", StringValue("1.0Mbps"));
	csma3.SetChannelAttribute("Delay", TimeValue(NanoSeconds(500)));

	NetDeviceContainer csmaDevices3;
	csmaDevices3 = csma3.Install(csmaNodes3);
	//CMSA4网络拓扑
	CsmaHelper csma4;
	csma4.SetChannelAttribute("DataRate", StringValue("1.0Mbps"));
	csma4.SetChannelAttribute("Delay", TimeValue(NanoSeconds(500)));

	NetDeviceContainer csmaDevices4;
	csmaDevices4 = csma4.Install(csmaNodes4);
	//CMSA5网络拓扑
	CsmaHelper csma5;
	csma5.SetChannelAttribute("DataRate", StringValue("1.0Mbps"));
	csma5.SetChannelAttribute("Delay", TimeValue(NanoSeconds(500)));

	NetDeviceContainer csmaDevices5;
	csmaDevices5 = csma5.Install(csmaNodes5);
	//CMSA6网络拓扑
	CsmaHelper csma6;
	csma6.SetChannelAttribute("DataRate", StringValue("1.0Mbps"));
	csma6.SetChannelAttribute("Delay", TimeValue(NanoSeconds(500)));

	NetDeviceContainer csmaDevices6;
	csmaDevices6 = csma6.Install(csmaNodes6);
	//CMSA7网络拓扑
	CsmaHelper csma7;
	csma7.SetChannelAttribute("DataRate", StringValue("1.5Mbps"));
	csma7.SetChannelAttribute("Delay", TimeValue(NanoSeconds(500)));

	NetDeviceContainer csmaDevices7;
	csmaDevices7 = csma7.Install(csmaNodes7);



	//安装协议栈（每个node只有一个stack）
	InternetStackHelper stack;
	stack.Install(csmaNodes1);
	stack.Install(csmaNodes2);
	stack.Install(csmaNodes3);
	stack.Install(csmaNodes4);
	stack.Install(csmaNodes5.Get(0));
	stack.Install(csmaNodes6.Get(0));
	stack.Install(csmaNodes7.Get(0));

	//在p2p网络上分配地址  node0：10.1.1.1；node1： 10.1.1.2
	Ipv4AddressHelper address;


	//在CSMA1网络上分配地址，相当于t1下端口IP为10.0.1.1，其余主机为n1 IP为10.0.1.2
	//n2主机IP为10.0.1.3
	address.SetBase("10.0.1.0", "255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces1;
	csmaInterfaces1 = address.Assign(csmaDevices1);
	//在CSMA2网络上分配地址，同CSMA1网络IP分配
	address.SetBase("10.0.2.0", "255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces2;
	csmaInterfaces2 = address.Assign(csmaDevices2);
	//在CSMA3网络上分配地址，同CSMA1网络IP分配
	address.SetBase("10.0.3.0", "255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces3;
	csmaInterfaces3 = address.Assign(csmaDevices3);
	//在CSMA4网络上分配地址，同CSMA1网络IP分配
	address.SetBase("10.0.4.0", "255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces4;
	csmaInterfaces4 = address.Assign(csmaDevices4);
	//在CSMA5网络上分配地址，相当于a1下端口IP为10.1.1.1，其余交换机为t1上端口 IP为10.1.1.2
	//t2上端口IP为10.1.1.3
	address.SetBase("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces5;
	csmaInterfaces5 = address.Assign(csmaDevices5);
	//在CSMA6网络上分配地址，同CSMA5中网络IP分配
	address.SetBase("10.2.1.0", "255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces6;
	csmaInterfaces6 = address.Assign(csmaDevices6);
	//在CSMA7网络上分配地址，相当于c1端口IP为192.168.1.1，其余交换机为a1上端口 IP为192.168.1.2
	//t2上端口IP为192.168.1.3
	address.SetBase("192.168.1.0", "255.255.255.0");
	Ipv4InterfaceContainer csmaInterfaces7;
	csmaInterfaces7 = address.Assign(csmaDevices7);

	//zhuji h1 server
	ApplicationContainer sinkApp1;
	PacketSinkHelper packetSinkHelper1("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces1.GetAddress(1), 5000));
	sinkApp1 = packetSinkHelper1.Install(csmaNodes1.Get(1));
	sinkApp1.Start(Seconds(1.0));
	sinkApp1.Stop(Seconds(60.0));
	//zhuji h2 server 
	ApplicationContainer sinkApp2;
	PacketSinkHelper packetSinkHelper2("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces1.GetAddress(2), 5000));
	sinkApp2 = packetSinkHelper2.Install(csmaNodes1.Get(2));
	sinkApp2.Start(Seconds(1.0));
	sinkApp2.Stop(Seconds(60.0));
	//zhuji h3 server
	ApplicationContainer sinkApp3;
	PacketSinkHelper packetSinkHelper3("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces2.GetAddress(1), 5000));
	sinkApp3 = packetSinkHelper3.Install(csmaNodes2.Get(1));
	sinkApp3.Start(Seconds(1.0));
	sinkApp3.Stop(Seconds(60.0));
	//zhuji h4 server
	ApplicationContainer sinkApp4;
	PacketSinkHelper packetSinkHelper4("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces2.GetAddress(2), 5000));
	sinkApp4 = packetSinkHelper4.Install(csmaNodes2.Get(2));
	sinkApp4.Start(Seconds(1.0));
	sinkApp4.Stop(Seconds(60.0));
	//zhuji h5 server
	ApplicationContainer sinkApp5;
	PacketSinkHelper packetSinkHelper5("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces3.GetAddress(1), 5000));
	sinkApp5 = packetSinkHelper5.Install(csmaNodes3.Get(1));
	sinkApp5.Start(Seconds(1.0));
	sinkApp5.Stop(Seconds(60.0));
	//zhuji h6 server
	ApplicationContainer sinkApp6;
	PacketSinkHelper packetSinkHelper6("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces3.GetAddress(2), 5000));
	sinkApp6 = packetSinkHelper6.Install(csmaNodes3.Get(2));
	sinkApp6.Start(Seconds(1.0));
	sinkApp6.Stop(Seconds(60.0));
	//zhuji h7 server
	ApplicationContainer sinkApp7;
	PacketSinkHelper packetSinkHelper7("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces4.GetAddress(1), 5000));
	sinkApp7 = packetSinkHelper7.Install(csmaNodes4.Get(1));
	sinkApp7.Start(Seconds(1.0));
	sinkApp7.Stop(Seconds(60.0));
	//zhuji h8 server
	ApplicationContainer sinkApp8;
	PacketSinkHelper packetSinkHelper8("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces4.GetAddress(2), 5000));
	sinkApp8 = packetSinkHelper8.Install(csmaNodes4.Get(2));
	sinkApp8.Start(Seconds(1.0));
	sinkApp8.Stop(Seconds(60.0));


	//在节点n1上建立多个OnOffApplication，产生多路流量,用于接收其他客户机发来的数据包
	//On/Off周期性地产生流量，这里将On周期设置为50秒，Off周期设置为0
	  //zhuji   h1--->h2
	ApplicationContainer clientApp1;
	OnOffHelper client1("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces1.GetAddress(2), 5000));
	client1.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	client1.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	client1.SetAttribute("DataRate", DataRateValue(DataRate("1.5Mbps")));
	client1.SetAttribute("PacketSize", UintegerValue(2000));
	clientApp1 = client1.Install(csmaNodes1.Get(1));
	clientApp1.Start(Seconds(2));
	clientApp1.Stop(Seconds(3));
	//zhuji   h1--->h3
	ApplicationContainer clientApp2;
	OnOffHelper client2("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces2.GetAddress(1), 5000));
	client2.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	client2.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	client2.SetAttribute("DataRate", DataRateValue(DataRate("1.5Mbps")));
	client2.SetAttribute("PacketSize", UintegerValue(2000));
	clientApp2 = client2.Install(csmaNodes1.Get(1));
	clientApp2.Start(Seconds(2));
	clientApp2.Stop(Seconds(3));
	//zhuji  h5--->h6
	ApplicationContainer clientApp3;
	OnOffHelper client3("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces3.GetAddress(2), 5000));
	client3.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	client3.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	client3.SetAttribute("DataRate", DataRateValue(DataRate("1.5Mbps")));
	client3.SetAttribute("PacketSize", UintegerValue(2000));
	clientApp3 = client3.Install(csmaNodes3.Get(1));
	clientApp3.Start(Seconds(2));
	clientApp3.Stop(Seconds(3));
	//zhuji  h5--->h7
	ApplicationContainer clientApp4;
	OnOffHelper client4("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces4.GetAddress(1), 5000));
	client4.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	client4.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	client4.SetAttribute("DataRate", DataRateValue(DataRate("1.5Mbps")));
	client4.SetAttribute("PacketSize", UintegerValue(2000));
	clientApp4 = client4.Install(csmaNodes3.Get(1));
	clientApp4.Start(Seconds(2));
	clientApp4.Stop(Seconds(3));
	//zhuji  h1--->h5
	ApplicationContainer clientApp5;
	OnOffHelper client5("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces3.GetAddress(1), 5000));
	client5.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	client5.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	client5.SetAttribute("DataRate", DataRateValue(DataRate("1.5Mbps")));
	client5.SetAttribute("PacketSize", UintegerValue(2000));
	clientApp5 = client5.Install(csmaNodes1.Get(1));
	clientApp5.Start(Seconds(2));
	clientApp5.Stop(Seconds(3));
	//zhuji  h6--->h2
	ApplicationContainer clientApp6;
	OnOffHelper client6("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces1.GetAddress(2), 5000));
	client6.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	client6.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	client6.SetAttribute("DataRate", DataRateValue(DataRate("1.5Mbps")));
	client6.SetAttribute("PacketSize", UintegerValue(2000));
	clientApp6 = client6.Install(csmaNodes3.Get(2));
	clientApp6.Start(Seconds(2));
	clientApp6.Stop(Seconds(3));
	//zhuji  h3--->h7
	ApplicationContainer clientApp7;
	OnOffHelper client7("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces4.GetAddress(1), 5000));
	client7.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	client7.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	client7.SetAttribute("DataRate", DataRateValue(DataRate("1.5Mbps")));
	client7.SetAttribute("PacketSize", UintegerValue(2000));
	clientApp7 = client7.Install(csmaNodes2.Get(1));
	clientApp7.Start(Seconds(2));
	clientApp7.Stop(Seconds(3));
	//zhuji  h8--->h4
	ApplicationContainer clientApp8;
	OnOffHelper client8("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces2.GetAddress(2), 5000));
	client8.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	client8.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	client8.SetAttribute("DataRate", DataRateValue(DataRate("1.5Mbps")));
	client8.SetAttribute("PacketSize", UintegerValue(2000));
	clientApp8 = client8.Install(csmaNodes4.Get(2));
	clientApp8.Start(Seconds(2));
	clientApp8.Stop(Seconds(3));
	//zhuji  h2--->h8
	ApplicationContainer clientApp9;
	OnOffHelper client9("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces4.GetAddress(2), 5000));
	client9.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	client9.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	client9.SetAttribute("DataRate", DataRateValue(DataRate("1.5Mbps")));
	client9.SetAttribute("PacketSize", UintegerValue(2000));
	clientApp9 = client9.Install(csmaNodes1.Get(2));
	clientApp9.Start(Seconds(2));
	clientApp9.Stop(Seconds(3));
	//zhuji  h5--->h8
	ApplicationContainer clientApp10;
	OnOffHelper client10("ns3::TcpSocketFactory", InetSocketAddress(csmaInterfaces4.GetAddress(2), 5000));
	client10.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=50]"));
	client10.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
	client10.SetAttribute("DataRate", DataRateValue(DataRate("1.5Mbps")));
	client10.SetAttribute("PacketSize", UintegerValue(2000));
	clientApp10 = client10.Install(csmaNodes3.Get(1));
	clientApp10.Start(Seconds(2));
	clientApp10.Stop(Seconds(3));


	Ipv4GlobalRoutingHelper::PopulateRoutingTables();
	csma1.EnablePcap("dc2", csmaNodes1.Get(1)->GetId(), 0, false);// csmaDevices1.Get (1));
	csma1.EnablePcap("dc2", csmaNodes1.Get(2)->GetId(), 0, false);// csmaDevices1.Get (2));
	csma2.EnablePcap("dc2", csmaNodes2.Get(1)->GetId(), 0, false);// csmaDevices2.Get (1));
	csma2.EnablePcap("dc2", csmaNodes2.Get(2)->GetId(), 0, false);// csmaDevices2.Get (2));
	csma3.EnablePcap("dc2", csmaNodes3.Get(1)->GetId(), 0, false);// csmaDevices3.Get (1));
	csma3.EnablePcap("dc2", csmaNodes3.Get(2)->GetId(), 0, false);// csmaDevices3.Get (2));
	csma4.EnablePcap("dc2", csmaNodes4.Get(1)->GetId(), 0, false);// csmaDevices4.Get (1));
	csma4.EnablePcap("dc2", csmaNodes4.Get(2)->GetId(), 0, false);// csmaDevices4.Get (2));


	  //AnimationInterface anim("dc.xml"); 





	Simulator::Run();
	Simulator::Destroy();
	return 0;
}
