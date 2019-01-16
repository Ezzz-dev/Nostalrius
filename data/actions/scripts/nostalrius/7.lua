function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32864, y = 32556, z = 11}, 1563) then
		item:transform(2773, 1)
		item:decay()
		Game.sendMagicEffect({x = 32864, y = 32556, z = 11}, 14)
		Game.removeItemOnMap({x = 32864, y = 32556, z = 11}, 1563)
	elseif item:getId() == 2772 and not Game.isItemThere({x = 32864, y = 32556, z = 11}, 1563) then
		player:sendCancelMessage("The lever won't budge.")
	elseif item:getId() == 2773 and not Game.isItemThere({x = 32864, y = 32556, z = 11}, 1563) then
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32864, y = 32556, z = 11},{x = 32864, y = 32557, z = 11})
		Game.sendMagicEffect({x = 32864, y = 32556, z = 11}, 14)
		Game.createItem(1563, 1, {x = 32864, y = 32556, z = 11})
	elseif item:getId() == 2773 then
		player:sendCancelMessage("The lever won't budge.")
	end
	return true
end