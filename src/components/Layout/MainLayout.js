
import React from 'react';
import AgentsSidebar from '../Sidebar/AgentsSidebar';
import ChatArea from '../MainContent/ChatArea';

const MainLayout = () => {
  return (
    <div className="main-layout">
      <AgentsSidebar />
      <ChatArea />
    </div>
  );
};

export default MainLayout;
