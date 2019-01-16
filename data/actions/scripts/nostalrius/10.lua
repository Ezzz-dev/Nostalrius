function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32792, y = 31581, z = 07},1282) then 
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32792, y = 31581, z = 07}, 1282)
	elseif item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2773 and Game.isItemThere({x = 32792, y = 31581, z = 07}, 1282) then
		item:transform(2772, 1)
		item:decay()
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32792, y = 31581, z = 07},{x = 32792, y = 31582, z = 07})
		Game.createItem(1282, 1, {x = 32792, y = 31581, z = 07})
	end
	return true
end