function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32483, y = 31633, z = 09}, 385) then
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		Game.transformItemOnMap({x = 32483, y = 31633, z = 09}, 355, 385)
	elseif item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
	end
	return true
end