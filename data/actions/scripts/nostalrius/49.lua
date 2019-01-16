function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		Game.createItem(2471, 1, {x = 32479, y = 31901, z = 05})
		Game.createItem(2122, 1, {x = 32479, y = 31892, z = 03})
	elseif item:getId() == 2773 and not Game.isItemThere({x = 32479, y = 31892, z = 03}, 2122) then
		item:transform(2772, 1)
		item:decay()
	end
	return true
end