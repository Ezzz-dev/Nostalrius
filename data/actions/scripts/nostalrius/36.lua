function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		Game.transformItemOnMap({x = 32605, y = 31902, z = 04}, 436, 432)
		item:transform(2773, 1)
		item:decay()
		doRelocate({x = 32605, y = 31902, z = 04},{x = 32605, y = 31902, z = 05})
	elseif item:getId() == 2773 then 
		Game.transformItemOnMap({x = 32605, y = 31902, z = 04}, 432, 436)
		item:transform(2772, 1)
		item:decay()
	end
	return true
end