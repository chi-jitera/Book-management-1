<changes><change><info>Add comments to describe the purpose and functionality of the MainLayout component.</info><content>import React from 'react';
import AgentsSidebar from '../Sidebar/AgentsSidebar';
import ChatArea from '../MainContent/ChatArea';

/**
 * MainLayout component integrates the sidebar and chat area components.
 * It serves as the main layout for the application, providing a structured
 * view with a sidebar for agent navigation and a main content area for chat.
 */
const MainLayout = () => {
  return (
    <div className="main-layout">
      <AgentsSidebar />
      <ChatArea />
    </div>
  );
};

export default MainLayout;</content></change>
          </changes>