function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2774 and Game.isItemThere({x = 33151, y = 32866, z = 08},1345) then 
		Game.removeItemOnMap({x = 33151, y = 32866, z = 08}, 1345)
		Game.sendMagicEffect({x = 33151, y = 32862, z = 07}, 14)
	elseif item:getId() == 2774 then 
		Game.sendMagicEffect({x = 33151, y = 32862, z = 07}, 3)
	end
	return true
end