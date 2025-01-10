import { OrderTable } from './components/OrderTable'
import { useState, useEffect } from 'react';
import { Routes, Route, useParams } from "react-router-dom";
import { OrderForm } from './components/OrderForm';
import { OrderSearch } from './components/OrderSearch';
import { URL } from './Utils/constants';


const App = () => {

  const [isOrderView, setView] = useState(false)
  const [allOrders, setAllOrders] = useState([])
  const { id } = useParams();


  return (
    <div>
      <OrderSearch></OrderSearch>
      <div>
        <div>
          <Routes>
            <Route path="/" element={<div>Welcome</div>}></Route>
            <Route path='/orders' element={<OrderTable/>}></Route>
            <Route path='/create' element={<OrderForm sandwiches />}></Route>
            <Route path='/orders/:id' element={<OrderTable/>} />
          </Routes>
        </div>
        {isOrderView &&
          <OrderTable />
        }
      </div>
    </div>

  )
}


export default App
